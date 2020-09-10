// I2C Address
#define HMC_ADDR                0x1E  
// Registers
#define CONFIG_REG_A            0x00
#define CONFIG_REG_B            0x01
#define MODE_REG                0x02
#define HMC_DATA                0x03
// Register Data
#define CONF_REGA_DATA          0x34      // 2 samples per reading, 30Hz data rate
#define CONF_REGB_DATA          0x20      // -2048 to 2047, Sensor range +-1.3 Gauss or +- 130 uT
#define MODE_REG_DATA           0x00      // Continuous measurement mode
// Misc
#define MAG_SCALE_FACTOR        15.746f   // 2047/130
#define HMC_LENGTH              6

void HMCInit(){
  WriteI2CRegister(HMC_ADDR,CONFIG_REG_A,CONF_REGA_DATA);
  WriteI2CRegister(HMC_ADDR,CONFIG_REG_B,CONF_REGB_DATA);
  WriteI2CRegister(HMC_ADDR,MODE_REG,MODE_REG_DATA);
}

void RawHMCRead(){                            
  int i = 0;
  int i2cdata[HMC_LENGTH];
  Vector TempMag;

  ReadI2CData(HMC_ADDR,HMC_DATA,HMC_LENGTH);                                            
  while(Wire.available()){ 
    i2cdata[i] = Wire.read();                                                           
    i++;
  }
  Wire.endTransmission(); 
  if (i==HMC_LENGTH){
    RawMag.x = ((float)((i2cdata[4] << 8) | i2cdata[5]))/-MAG_SCALE_FACTOR;
    RawMag.y = ((float)((i2cdata[0] << 8) | i2cdata[1]))/ MAG_SCALE_FACTOR;
    RawMag.z = ((float)((i2cdata[2] << 8) | i2cdata[3]))/-MAG_SCALE_FACTOR;
  }
  else {
    Serial.println("!ERR: Mag data");
  }
}

void CalibrateMag(){
  Serial.println("Starting Cal Samples");
  while (CalFlag == true){
    RawHMCRead();
    if (RawMag.x > MagC.Xmax){
      MagC.Xmax = RawMag.x;
    }
    if (RawMag.x < MagC.Xmin){
      MagC.Xmin = RawMag.x;
    }  
    if (RawMag.y > MagC.Ymax){
      MagC.Ymax = RawMag.y;
    }
    if (RawMag.y < MagC.Ymin){
      MagC.Ymin = RawMag.y;
    }
    if (RawMag.z > MagC.Zmax){
      MagC.Zmax = RawMag.z;
    }
    if (RawMag.z < MagC.Zmin){
      MagC.Zmin = RawMag.z;
    }  
    delay(50);
    if (Serial.read() == 's'){
      CalFlag = false;
    }
  }  

  float Xmm = MagC.Xmax - MagC.Xmin;
  float Ymm = MagC.Ymax - MagC.Ymin;
  float Zmm = MagC.Zmax - MagC.Zmin;
  
  MagC.Xscale = ((Ymm + Zmm)/2.0)/(Xmm);
  MagC.Yscale = ((Xmm + Zmm)/2.0)/(Ymm);
  MagC.Zscale = ((Xmm + Ymm)/2.0)/(Zmm);
  MagC.Xbias = MagC.Xscale*(0.5*Xmm - MagC.Xmax);
  MagC.Ybias = MagC.Yscale*(0.5*Ymm - MagC.Ymax);
  MagC.Zbias = MagC.Zscale*(0.5*Zmm - MagC.Zmax);
  Serial.print(MagC.Xscale);
  Serial.print(",");
  Serial.print(MagC.Xbias);
  Serial.print(", ");
  Serial.print(MagC.Yscale);
  Serial.print(", ");
  Serial.print(MagC.Ybias);
  Serial.print(", ");
  Serial.print(MagC.Zscale);
  Serial.print(", ");
  Serial.println(MagC.Zbias);
  
  Serial.println("Finished Cal");
  while(1){
  }
}

void HMCRead(){
  RawHMCRead();
  Mag.x = MagC.Xscale*RawMag.x + MagC.Xbias;
  Mag.y = MagC.Yscale*RawMag.y + MagC.Ybias;
  Mag.z = MagC.Zscale*RawMag.z + MagC.Zbias;
  
  float norm = sqrt(Mag.x*Mag.x + Mag.y*Mag.y + Mag.z*Mag.z);
  NormMag.x = Mag.x/norm;
  NormMag.y = Mag.y/norm;
  NormMag.z = Mag.z/norm;
}
  
