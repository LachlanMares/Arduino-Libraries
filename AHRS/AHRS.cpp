#include "AHRS.h"

AHRS::AHRS(){
  _GetNewSample = false;
  _GetNewMagSample = false;
  _Running = true;
}

void AHRS::Init(byte Sample_Rate,byte Accl_Config,byte Gyro_Config,float CutoffFreq){

  ResetQuaternion(&_Q); 
  ResetVector(&_Accl);
  ResetVector(&_Mag); 
 
  switch(Sample_Rate){
    case MPU_SAMPLE_200HZ:
      _DT = 0.005f;
      break;
    case MPU_SAMPLE_166HZ:
      _DT = 0.00602f;
      break;   
    case MPU_SAMPLE_142HZ:
      _DT = 0.00704f;
      break;   
    case MPU_SAMPLE_125HZ:
      _DT = 0.008f;
      break;
    case MPU_SAMPLE_100HZ:
      _DT = 0.01f;
      break;
    case MPU_SAMPLE_50HZ:
      _DT = 0.02f;
      break;
  } 
  
  _MagDT = MAG_FREQ * _DT;
  
  switch(Accl_Config){
    case BITS_ACC_2G:
      SetVectorTo(&_AcclScale,32768.0f/2.0f);
      break;
    case BITS_ACC_4G:
      SetVectorTo(&_AcclScale,32768.0f/4.0f);
      break;   
    case BITS_ACC_8G:
      SetVectorTo(&_AcclScale,32768.0f/8.0f);
      break;   
    case BITS_ACC_16G:
      SetVectorTo(&_AcclScale,32768.0f/16.0f);
      break;
    default:
      SetVectorTo(&_AcclScale,ACC_SCALE_FACTOR);
      break;
  }
    
  WriteI2C(MPU6050_ADDR,MPUREG_PWR_MGMT_1,BIT_H_RESET);    
  delay(50);  
  WriteI2C(MPU6050_ADDR,MPUREG_PWR_MGMT_1,MPU_CLK_SEL_PLLGYROZ); 
  WriteI2C(MPU6050_ADDR,MPUREG_SMPLRT_DIV,Sample_Rate);
  WriteI2C(MPU6050_ADDR,MPUREG_CONFIG,BITS_DLPF_CFG_42HZ);
  WriteI2C(MPU6050_ADDR,MPUREG_GYRO_CONFIG,Gyro_Config);
  WriteI2C(MPU6050_ADDR,MPUREG_ACCEL_CONFIG,Accl_Config);
  WriteI2C(MPU6050_ADDR,MPUREG_INT_ENABLE,BIT_RAW_RDY_EN);
  WriteI2C(MPU6050_ADDR,MPUREG_INT_PIN_CFG,BIT_INT_ANYRD_2CLEAR);  

  float _Wc = TWO_M_PI*CutoffFreq;
  float _c = 1.0f/(tan((_Wc*_DT)/2.0f));
  float _G = _c*_c + SQRT2*_c + 1.0f;
  _Phi.Yc[0] = (2.0f - 2.0f*_c*_c)/_G;
  _Phi.Yc[1] = (_c*_c - SQRT2*_c + 1.0f)/_G;
  _Phi.Xc[0] = 1.0f/_G;
  _Phi.Xc[1] = 2.0f/_G;
  _Phi.Xc[2] = 1.0f/_G;
  _Theta.Yc[0] = _Phi.Yc[0]; 
  _Theta.Yc[1] = _Phi.Yc[1];
  _Theta.Xc[0] = _Phi.Xc[0];
  _Theta.Xc[1] = _Phi.Xc[1];
  _Theta.Xc[2] = _Phi.Xc[2];
  
  _Wc = TWO_M_PI*(CutoffFreq/MAG_FREQ);
  _c = 1.0f/(tan((_Wc*_MagDT)/2.0f));
  _G = _c*_c + SQRT2*_c + 1.0f; 
  _Psi.Yc[0] = (2.0f - 2.0f*_c*_c)/_G;
  _Psi.Yc[1] = (_c*_c - SQRT2*_c + 1.0f)/_G;
  _Psi.Xc[0] = 1.0f/_G;
  _Psi.Xc[1] = 2.0f/_G;
  _Psi.Xc[2] = 1.0f/_G;
  
  _SampleCounter = 0;
  _MagCounter = 0;

  WriteI2C(AK8975C_ADDR,AK8975C_CNTL,SINGLE_READING);
}

void AHRS::Start(){
  _Running = true;
}

void AHRS::Stop(){
  _Running = false;
}

void AHRS::AHRS_ISR(){
  if(_Running){
    _GetNewSample = true;
  }
  if(_Running){
    _MagCounter++;
    if(_MagCounter == MAG_FREQ){
      _MagCounter = 0;
      _GetNewMagSample = true;
    }
  }  
}

void AHRS::Update(){
  if(_GetNewMagSample){
    _GetNewMagSample = false;
    ReadI2C(AK8975C_ADDR,AK8975C_HXL,AK8975C_LENGTH);
    _i = 0;
    while(Wire.available()){ 
      _i2cdata[_i] = Wire.read();                                  
      _i++;
    }
    Wire.endTransmission();  
    Vector _TempMag;
    if (_i==AK8975C_LENGTH){                                                                                                                                                  
      _TempMag.x = ((float)((_i2cdata[3] << 8) | _i2cdata[2])) * -1.0f;                           
      _TempMag.y =  (float)((_i2cdata[1] << 8) | _i2cdata[0]);                           
      _TempMag.z =  (float)((_i2cdata[5] << 8) | _i2cdata[4]);                           
      _Mag.x = MAG_XS*_TempMag.x + MAG_XB;
      _Mag.y = MAG_YS*_TempMag.y + MAG_YB;
      _Mag.z = MAG_ZS*_TempMag.z + MAG_ZB;
      NormaliseVector(&_Mag);

      WriteI2C(AK8975C_ADDR,AK8975C_CNTL,SINGLE_READING); 
      
      if(CheckInputValid(&_Mag) && abs(_EulerAngles.phi) < MAX_MAG_ANGLE && abs(_EulerAngles.theta) < MAX_MAG_ANGLE){
        float _TempPsi = atan2(-_Mag.y,_Mag.x) + MAGNETIC_DECLINATION;
        while (_TempPsi > TWO_M_PI){                                                                      // Want to see a heading of 0 to 359 degrees
          _TempPsi -= TWO_M_PI;
        } 
        while (_TempPsi < 0.0f){                                                                          // Want to see a heading of 0 to 359 degrees
          _TempPsi += TWO_M_PI;
        } 
        _EulerAngles.psi = UpdateFilter(&_Psi,_TempPsi);
      }
    } else {
        Serial.println("!ERR: Mag data");                                                          
     }
  }                                                            

  if(_GetNewSample && _Running){
    _GetNewSample = false;
    _i = 0;
    Vector _TempAccl;
    ReadI2C(MPU6050_ADDR,MPUREG_ACCEL_XOUT_H,ACCL_DATA_LENGTH); 
    while(Wire.available()){ 
      _i2cdata[_i] = Wire.read();                                  
      _i++;
    }
    Wire.endTransmission();                                         
    if (_i==ACCL_DATA_LENGTH){ 
      _TempAccl.x = (((float)((_i2cdata[2] << 8) | _i2cdata[3])) / _AcclScale.x) * -1.0f;                                                      
      _TempAccl.y = (((float)((_i2cdata[0] << 8) | _i2cdata[1])) / _AcclScale.y);      
      _TempAccl.z = (((float)((_i2cdata[4] << 8) | _i2cdata[5])) / _AcclScale.z);  
      _Accl.x = ACC_XS*_TempAccl.x + ACC_XB;
      _Accl.y = ACC_YS*_TempAccl.y + ACC_YB;
      _Accl.z = ACC_ZS*_TempAccl.z + ACC_ZB; 
      NormaliseVector(&_Accl);
   
      if (CheckInputValid(&_Accl)){ 
        QFromAccl(_Accl,&_Q);
        _EulerAngles.phi = UpdateFilter(&_Phi,SetPhiFromQuaternion(&_Q));
        _EulerAngles.theta = UpdateFilter(&_Theta,SetThetaFromQuaternion(&_Q));
      }
    } else {
        Serial.println("!ERR: MPU data");                                                          
      }
  }
}

void AHRS::GetEulerAnglesRad(Euler* EAng){
  EAng->phi = _EulerAngles.phi;
  EAng->theta = _EulerAngles.theta;
  EAng->psi = _EulerAngles.psi;
}

void AHRS::GetEulerAnglesDeg(Euler* EAng){
  EAng->phi = TO_DEG(_EulerAngles.phi);
  EAng->theta = TO_DEG(_EulerAngles.theta);
  EAng->psi = TO_DEG(_EulerAngles.psi);
}

void AHRS::Acclerometer(Vector* Accl){
  Accl->x = _Accl.x;
  Accl->y = _Accl.y;
  Accl->z = _Accl.z;
}

void AHRS::Magnetometer(Vector* Mag){
  Mag->x = _Mag.x;
  Mag->y = _Mag.y;
  Mag->z = _Mag.z;
}

void AHRS::ResetQuaternion(Quaternion* Qt){
  Qt->w = 1.0f;
  Qt->x = 0.0f;
  Qt->y = 0.0f;  
  Qt->z = 0.0f;  
}  

void AHRS::NormaliseQuaternion(Quaternion* Qt){
  float _Norm = sqrt(Qt->w*Qt->w + Qt->x*Qt->x + Qt->y*Qt->y + Qt->z*Qt->z); 
  Qt->w /= _Norm;
  Qt->x /= _Norm;
  Qt->y /= _Norm;
  Qt->z /= _Norm;
}

void AHRS::ScaledCopyQ(Quaternion* Qt,float St,Quaternion* Qt2){
  Qt2->w = Qt->w * St;
  Qt2->x = Qt->x * St;
  Qt2->y = Qt->y * St;
  Qt2->z = Qt->z * St;
} 

void AHRS::QFromAccl(Vector At,Quaternion* Qr){
  Vector _N;
  _N.x = At.x;                                                                                     
  _N.y = At.y;                                                                                     
  _N.z = At.z + 1.0f;
  NormaliseVector(&_N);
  Qr->w = (At.x*_N.x + At.y*_N.y + At.z*_N.z);                                                           
  Qr->x = (At.y*_N.z) - (At.z*_N.y);                                                                   
  Qr->y = (At.z*_N.x) - (At.x*_N.z);
  Qr->z = (At.x*_N.y) - (At.y*_N.x);
  NormaliseQuaternion(Qr); 
}

float AHRS::SetPhiFromQuaternion(Quaternion* Qt){
  return (atan2(2.0f*Qt->w*Qt->x - 2.0f*Qt->y*Qt->z , 1.0f - 2.0f*Qt->x*Qt->x - 2.0f*Qt->y*Qt->y));
}

float AHRS::SetThetaFromQuaternion(Quaternion* Qt){
  return (asin(2.0f*Qt->w*Qt->y + 2.0f*Qt->z*Qt->x));
}
 
float AHRS::SetPsiFromQuaternion(Quaternion* Qt){
 return (atan2(2.0f*Qt->w*Qt->z - 2.0f*Qt->x*Qt->y , 1.0f - 2.0f*Qt->y*Qt->y - 2.0f*Qt->z*Qt->z));
} 

void AHRS::ResetVector(Vector* Vt){
  Vt->x = 0.0f;
  Vt->y = 0.0f;  
  Vt->z = 0.0f;  
}  

void AHRS::NormaliseVector(Vector* Vt){
  float _Norm = sqrt(Vt->x*Vt->x + Vt->y*Vt->y + Vt->z*Vt->z); 
  Vt->x /= _Norm;
  Vt->y /= _Norm;
  Vt->z /= _Norm;
}

void AHRS::SetVectorTo(Vector* Vt,float Ft){
  Vt->x = Ft;
  Vt->y = Ft;
  Vt->z = Ft;
}

boolean AHRS::CheckInputValid(Vector* Vt){
  boolean RetVal = true;
  if(abs(Vt->x) < VALID_LIMIT && abs(Vt->y) < VALID_LIMIT && abs(Vt->z) < VALID_LIMIT){
    RetVal = false;
  } 
  return RetVal;
}

float AHRS::UpdateFilter(ButterworthFilter* Filt,float NewReading){
  Filt->x[2] = Filt->x[1];
  Filt->x[1] = Filt->x[0];
  Filt->x[0] = NewReading;
  Filt->y[2] = Filt->y[1];
  Filt->y[1] = Filt->y[0]; 
  Filt->y[0] = Filt->Xc[0]*Filt->x[0] + Filt->Xc[1]*Filt->x[1] + Filt->Xc[2]*Filt->x[2] - Filt->Yc[0]*Filt->y[1] - Filt->Yc[1]*Filt->y[2];
  return Filt->y[0];
}

float AHRS::ScaleTwoFloats(float A,float B,float Scale){
  return (A*Scale + (1.0f-Scale)*B);
}

void AHRS::WriteI2C(byte I2CAddr,byte I2CReg, byte I2CData){                          // Function for writing a byte to a I2C slave
  Wire.beginTransmission(I2CAddr);
  Wire.write(I2CReg);                                
  Wire.write(I2CData);                                             
  Wire.endTransmission();
}

void AHRS::ReadI2C(byte I2CAddr,byte I2CReg, byte I2CLen){                            // Function for reading bytes from a I2C slave
  Wire.beginTransmission(I2CAddr); 
  Wire.write(I2CReg);                                      
  Wire.endTransmission();                                        
  Wire.beginTransmission(I2CAddr);                           
  Wire.requestFrom(I2CAddr,I2CLen);                               
}


