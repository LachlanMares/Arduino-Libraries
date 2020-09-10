void EulerFromMag(vector* _mag,vector* _earth,vector* Euler)
{
  boolean OnceFlag = true;
  boolean ObjectiveMet = false;
  int LoopCounter = -1;

  float StepSize = 0.05f;
  float Sr;
  float Cr;
  float St;
  float Ct;
  float Sp;
  float Cp;
  float norm;

  float R[3][3];
  float F[3];
  float JF[3][3];

  vector _euler;

  _euler.x = Euler->x;
  _euler.y = Euler->y;
  _euler.z = Euler->z;
 
  while (LoopCounter < 100 && !ObjectiveMet)
  {
    LoopCounter++;
  
    Sr = sin(_euler.x);
    Cr = cos(_euler.x);
    St = sin(_euler.y);
    Ct = cos(_euler.y);
    Sp = sin(_euler.z);
    Cp = cos(_euler.z);
 
    R[0][0] = Ct*Cp;
    R[0][1] = Ct*Sp;
    R[0][2] = -St;
  
    R[1][0] = Sr*St*Cp-Cr*Sp;
    R[1][1] = Cr*Cp+Sr*St*Sp;
    R[1][2] = Sr*Ct;
  
    R[2][0] = Cr*St*Cp+Sr*Sp;
    R[2][1] = Cr*St*Sp-Sr*Cp;
    R[2][2] = Cr*Ct;

       
    //F[0] = (R[0][0]*_earth->x + R[0][1]*_earth->y + R[0][2]*_earth->z) -_mag->x;
    //F[1] = (R[1][0]*_earth->x + R[1][1]*_earth->y + R[1][2]*_earth->z) -_mag->y;
    //F[2] = (R[2][0]*_earth->x + R[2][1]*_earth->y + R[2][2]*_earth->z) -_mag->z;
    
    F[0] = ((Ct*Cp)*_earth->x + (Sr*St*Cp-Cr*Sp)*_earth->y + (Sr*Sp+Cr*St*Cp)*_earth->z) -_mag->x;
    F[1] = ((Ct*Sp)*_earth->x + (Cr*Cp+Sr*St*Sp)*_earth->y + (Cr*St*Sp-Sr*Cp)*_earth->z) -_mag->y;
    F[2] = ((-St)*_earth->x + (Sr*Ct)*_earth->y + (Cr*Ct)*_earth->z) -_mag->z;

    if(ComputeObjectiveFunction(F[0],F[1],F[2]) > 0.005f)
    {
           
      //JF[0][0] = 0;
      //JF[0][1] = (-St*Cp)*_earth->x + (-Ct*Sp)*_earth->y + (-Ct)*_earth->z;
      //JF[0][2] = (-Ct*Sp)*_earth->x + (Ct*Cp)*_earth->y;

      //JF[1][0] = (Sr*Sp+Cr*St*Cp)*_earth->x  + (Cr*Sp*St-Sr*Cp)*_earth->y + (Cr*Ct)*_earth->z;
      //JF[1][1] = (Sr*Ct*Cp)*_earth->x  + (Sr*Ct*Sp)*_earth->y + (-Sr*St)*_earth->z;
      //JF[1][2] = (-Cr*Cp-Sr*St*Sp)*_earth->x  + (-Cr*Sp*Ct+Sr*Cp)*_earth->y;
        
      //JF[2][0] = (-Sr*Sp*Cp+Cr*Sp)*_earth->x + (-Sr*Sp*Sp-Cr*Cp)*_earth->y + (-Sr*Ct)*_earth->z;
      //JF[2][1] = (Cr*Ct*Cp)*_earth->x + (-Cr*Ct*Sp)*_earth->y + (-Cr*St)*_earth->z;
      //JF[2][2] = (-Cr*Sp*Sp+Sr*Cp)*_earth->x + (Cr*Sp*Ct+Sr*Sp)*_earth->y;
      
      JF[0][0] = (Sr*Sp+Cr*St*Cp)*_earth->y + (Cr*Sp-Sr*St*Cp)*_earth->z;
      JF[0][1] = (-St*Cp)*_earth->x + (Sr*Ct*Cp)*_earth->y + (Cr*Ct*Cp)*_earth->z;
      JF[0][2] = (-Ct*Sp)*_earth->x + (-Cr*Cp-Sr*St*Sp)*_earth->y + (Sr*Cp-Cr*St*Sp)*_earth->z;
  
      JF[1][0] = (-Sr*Cp+Sr*St*Cp)*_earth->y + (-Cr*Cp-Sr*St*Sp)*_earth->z;
      JF[1][1] = (-St*Sp)*_earth->x + (Sr*Ct*Sp)*_earth->y + (-Cr*Ct*Sp)*_earth->z;
      JF[1][2] = (Ct*Cp)*_earth->x + (-Cr*Sp+Sr*St*Cp)*_earth->y + (Sr*Cp+Cr*St*Cp)*_earth->z;
  
      JF[2][0] = (Cr*Ct)*_earth->y + (-Sr*Ct)*_earth->z;
      JF[2][1] = (-Ct)*_earth->x + (-Sr*Ct)*_earth->y + (-Cr*St)*_earth->z;
      JF[2][2] = 0;

      _euler.x -= StepSize*(F[0]*JF[0][0] + F[1]*JF[1][0] + F[2]*JF[2][0]);
      _euler.y -= StepSize*(F[0]*JF[0][1] + F[1]*JF[1][1] + F[2]*JF[2][1]);
      _euler.z -= StepSize*(F[0]*JF[0][2] + F[1]*JF[1][2] + F[2]*JF[2][2]);

      norm = sqrt(_euler.x*_euler.x + _euler.y*_euler.y + _euler.z*_euler.z);

      _euler.x /= norm;
      _euler.y /= norm;
      _euler.z /= norm;
      
    } else 
      {
        ObjectiveMet = true;
      }
  }

  Euler->x = _euler.x;
  Euler->y = _euler.y;
  Euler->z = _euler.z;
  
  Serial.print("Loops ");
  Serial.println(LoopCounter);
  //Serial.print("Cost ");
  //Serial.println(ComputeObjectiveFunction(F[0],F[1],F[2]));
}

float ComputeObjectiveFunction(float cof0,float cof1,float cof2)
{
  float Cost = 0.5f*(cof0*cof0 + cof1*cof1 + cof2*cof2);
  return Cost;
}

void NormaliseVector(vector* _vec)
{
  float _Norm = sqrt(_vec->x*_vec->x + _vec->y*_vec->y + _vec->z*_vec->z);
  _vec->x /= _Norm;
  _vec->y /= _Norm;
  _vec->z /= _Norm;
}

void NormaliseQuarternion(quarternion* _quat)
{
  float _Norm = sqrt(_quat->w*_quat->w + _quat->x*_quat->x + _quat->y*_quat->y + _quat->z*_quat->z);
  _quat->w /= _Norm;
  _quat->x /= _Norm;
  _quat->y /= _Norm;
  _quat->z /= _Norm;
}

void ConjugateQuarternion(quarternion* _quat)
{
  _quat->x *= -1.0f;
  _quat->y *= -1.0f;
  _quat->z *= -1.0f;
}

void EulerFromMagNew(vector* _mag,vector* _earth,vector* _euler)
{
 /*vector _norm;
 _norm.x = _mag->x + _earth->x;
 _norm.y = _mag->y + _earth->y;
 _norm.z = _mag->z + _earth->z; 
 NormaliseVector(&_norm);
 _euler->x = (_mag->y*_norm.z) - (_mag->z*_norm.y);
 _euler->y = (_mag->z*_norm.x) - (_mag->x*_norm.z);
 _euler->z = (_mag->x*_norm.y) - (_mag->y*_norm.z);
*/
 _euler->x = (_mag->y*_earth->z) - (_mag->z*_earth->y);
 _euler->y = (_mag->z*_earth->x) - (_mag->x*_earth->z);
 _euler->z = (_mag->x*_earth->y) - (_mag->y*_earth->z);
}

void EulerAxisAngle(vector* _mag,vector* _earth,vector* _euler)
{
  NormaliseVector(_mag);
  NormaliseVector(_earth);
  
  float _angle = acos(_mag->x*_earth->x +_mag->y*_earth->y +_mag->z*_earth->z);
  vector _axis = {_mag->y*_earth->z - _mag->z*_earth->y , _mag->z*_earth->x - _mag->x*_earth->z , _mag->x*_earth->y - _mag->y*_earth->x};
  float sA = sin(_angle);
  float cA = cos(_angle);
  float tA = 1 - cA;

  if ((_axis.x*_axis.y*tA + _axis.z*sA) > 0.998)
  {
    _euler->x = 2.0*atan2(_axis.x*sin(_angle/2.0),cos(_angle/2.0));
    _euler->y = PI/2.0;
    _euler->z = 0.0;
  } else if ((_axis.x*_axis.y*tA + _axis.z*sA) < -0.998)
    {
      _euler->x = -2.0*atan2(_axis.x*sin(_angle/2.0),cos(_angle/2.0));
      _euler->y = -PI/2.0;
      _euler->z = 0.0;
    } else 
      {
        _euler->x = atan2(_axis.y*sA - _axis.x*_axis.z*tA , 1.0 - (_axis.y*_axis.y + _axis.z*_axis.z)*tA);
        _euler->y = asin(_axis.x*_axis.y*tA + _axis.z*sA);
        _euler->z = atan2(_axis.x*sA - _axis.y*_axis.z*tA , 1.0 - (_axis.x*_axis.x + _axis.z*_axis.z)*tA);
      }    
}



float QFromMag(vector* _mag,vector* _earth){
  vector _N;
  _N.x = _mag->x + _earth->x;                                                                                     
  _N.y = _mag->y + _earth->y;                                                                                     
  _N.z = _mag->z + _earth->z ;
  
  NormaliseVector(&_N);
  
  float Qw = (_mag->x*_N.x + _mag->y*_N.y + _mag->z*_N.z);                                                           
  float Qx = (_mag->y*_N.z) - (_mag->z*_N.y);                                                                   
  float Qy = (_mag->z*_N.x) - (_mag->x*_N.z);
  float Qz = (_mag->x*_N.y) - (_mag->y*_N.x);
  
  float _Norm = sqrt(Qw*Qw + Qx*Qx + Qy*Qy + Qz*Qz); 
  Qw /= _Norm;
  Qx /= _Norm;
  Qy /= _Norm;
  Qz /= _Norm;

  //return TO_DEG(atan2(2.0f*Qw*Qz + 2.0f*Qx*Qy , Qw*Qw + Qx*Qx - Qy*Qy - Qz*Qz));  
  return TO_DEG(atan2(Qx*Qy-Qw*Qz,0.5f-Qy*Qy-Qz*Qz));
}

void QFromAccl(vector* At,vector* _euler){
  vector _N;
  _N.x = At->x;                                                                                     
  _N.y = At->y;                                                                                     
  _N.z = At->z + 1.0f;
  NormaliseVector(&_N);
  
  float Qw = (At->x*_N.x + At->y*_N.y + At->z*_N.z);                                                           
  float Qx = (At->y*_N.z) - (At->z*_N.y);                                                                   
  float Qy = (At->z*_N.x) - (At->x*_N.z);
  float Qz = (At->x*_N.y) - (At->y*_N.x);
  
  float _Norm = sqrt(Qw*Qw + Qx*Qx + Qy*Qy + Qz*Qz); 
  Qw /= _Norm;
  Qx /= _Norm;
  Qy /= _Norm;
  Qz /= _Norm;
  
  _euler->x = atan2(2.0f*Qw*Qx - 2.0f*Qy*Qz , 1.0f - 2.0f*Qx*Qx - 2.0f*Qy*Qy);
  _euler->y = asin(2.0f*Qw*Qy + 2.0f*Qz*Qx);
}



