
void InitStructs(){
  MagC.Xmax = 0.0;
  MagC.Xmin = 0.0;
  MagC.Ymax = 0.0;
  MagC.Ymin = 0.0;
  MagC.Zmax = 0.0;
  MagC.Zmin = 0.0;
  MagC.Xscale = 1.0;
  MagC.Yscale = 1.0;
  MagC.Zscale = 1.0;
  MagC.Xbias = 0.0;
  MagC.Ybias = 0.0;
  MagC.Zbias = 0.0;
  
  float Norm = sqrt(EMagX*EMagX + EMagY*EMagY + EMagZ*EMagZ);
  if (EMagX != 0.0){
    EarthMag.x = EMagX/Norm;
  } else {
      EarthMag.x = 0.0;
    }
  if (EMagY != 0.0){
    EarthMag.y = EMagY/Norm;
  } else {
      EarthMag.y = 0.0;
    }
  if (EMagZ != 0.0){
    EarthMag.z = EMagZ/Norm;
  } else {
      EarthMag.z = 0.0;
    }
}

void WriteI2CRegister(byte Addr,byte Reg, byte Data){
  Wire.beginTransmission(Addr);
  Wire.write(Reg);                                
  Wire.write(Data);                                             
  Wire.endTransmission();
}

void ReadI2CData(byte Addr,byte Reg, byte Len){
  Wire.beginTransmission(Addr); 
  Wire.write(Reg);                                      
  Wire.endTransmission();                                        
  Wire.beginTransmission(Addr);                           
  Wire.requestFrom(Addr,Len);                               
}

void FastI2C(){                                     // 400KHz I2C
    TWBR = ((16000000L / 400000L) - 16) / 2;
}
  
void printdata(void){   
  Serial.print("Mag: ");
  Serial.print(Mag.x);
  Serial.print(", ");
  Serial.print(Mag.y);
  Serial.print(", ");
  Serial.print(Mag.z);
  Serial.print(" NormMag: ");
  Serial.print(NormMag.x);
  Serial.print(", ");
  Serial.print(NormMag.y);
  Serial.print(", ");
  Serial.print(NormMag.z);
  Serial.print(" EMag: ");
  Serial.print(EarthMag.x);
  Serial.print(", ");
  Serial.print(EarthMag.y);
  Serial.print(", ");
  Serial.println(EarthMag.z);
}

void InterruptRoutine(){
  UpdateFlag = true;
}
