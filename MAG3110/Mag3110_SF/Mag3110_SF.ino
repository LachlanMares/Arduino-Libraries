#include <Wire.h>

#define MAG_ADDR  0x0E //7-bit address for the MAG3110, doesn't change

#define MAG3110_LENGTH             6

#define MAG3110_ADDR               0x0E

#define MAG3110_DR_STATUS_REG      0x00
#define MAG3110_OUT_X_MSB_REG      0x01
#define MAG3110_OUT_X_LSB_REG      0x02
#define MAG3110_OUT_Y_MSB_REG      0x03
#define MAG3110_OUT_Y_LSB_REG      0x04
#define MAG3110_OUT_Z_MSB_REG      0x05
#define MAG3110_OUT_Z_LSB_REG      0x06
#define MAG3110_CTRL1_REG          0x10
#define MAG3110_CTRL2_REG          0x11

#define MAG3110_CTRL1_DEFAULT      0x1D
#define MAG3110_CTRL2_DEFAULT      0x80

#define MAG3110_ZYXDR_MASK         0x08

int magx,magy,magz;

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  config();            // turn the MAG3110 on
}

void loop()
{
  //print_values();
  if(DataReady())
  {
    readxyz();
    Serial.print("x=");
    Serial.print(magx); 
    Serial.print(",");  
    Serial.print("y=");    
    Serial.print(magy);
    Serial.print(",");       
    Serial.print("z=");    
    Serial.println(magz);
  }
}

void config(void)
{
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x10);              // cntrl register2
  Wire.write(MAG3110_CTRL1_DEFAULT);//0x80);              // send 0x80, enable auto resets
  Wire.endTransmission();       // stop transmitting
  
  delay(15);
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x11);              // cntrl register1
  Wire.write(MAG3110_CTRL2_DEFAULT);                 // send 0x01, active mode 
  Wire.endTransmission();       // stop transmitting
}

void print_values(void)
{
  Serial.print("x=");
  Serial.print(readx()); 
  Serial.print(",");  
  Serial.print("y=");    
  Serial.print(ready());
  Serial.print(",");       
  Serial.print("z=");    
  Serial.println(readz());      
}

int readx(void)
{
  int xl, xh;  //define the MSB and LSB
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x01);              // x MSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may send less than requested
  { 
    xh = Wire.read(); // receive the byte
  }
  
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x02);              // x LSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may send less than requested
  { 
    xl = Wire.read(); // receive the byte
  }
  
  int xout = (xl|(xh << 8)); //concatenate the MSB and LSB
  return xout;
}

int ready(void)
{
  int yl, yh;  //define the MSB and LSB
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x03);              // y MSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may send less than requested
  { 
    yh = Wire.read(); // receive the byte
  }
  
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x04);              // y LSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  while(Wire.available())    // slave may send less than requested
  { 
    yl = Wire.read(); // receive the byte
  }
  
  int yout = (yl|(yh << 8)); //concatenate the MSB and LSB
  return yout;
}

int readz(void)
{
  int zl, zh;  //define the MSB and LSB
  
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x05);              // z MSB reg
  Wire.endTransmission();       // stop transmitting
 
  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  Wire.requestFrom(MAG_ADDR, 2); // request 1 byte
  //while(Wire.available())    // slave may send less than requested
  //{ 
  //  zh = Wire.read(); // receive the byte
 // }
  
  //delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
 // Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  //Wire.write(0x06);              // z LSB reg
  //Wire.endTransmission();       // stop transmitting
 
  //delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
  //Wire.requestFrom(MAG_ADDR, 1); // request 1 byte
  //while(Wire.available())    // slave may send less than requested
  //{ 
    zl = Wire.read(); // receive the byte
  //}
  
  int zout = (zl|(zh << 8)); //concatenate the MSB and LSB
  return zout;
}

void readxyz(void)
{
  int _m[6];  //define the MSB and LSB

  Wire.beginTransmission(MAG_ADDR); 
  Wire.write(0x01);              
  Wire.endTransmission();     
    
  delayMicroseconds(2); 
    
  Wire.requestFrom(MAG_ADDR,6); 
  for(unsigned char k=0;k<6;k++)
  {
    _m[k] = Wire.read();
  }
   
  magx = (_m[1]|(_m[0] << 8));
  magy = (_m[3]|(_m[2] << 8));
  magz = (_m[5]|(_m[4] << 8));
}

bool DataReady()
{
   return (SingleRegisterRead(MAG3110_DR_STATUS_REG) & MAG3110_ZYXDR_MASK) ? true : false;
}

unsigned char SingleRegisterRead(unsigned char i2creg)
{
  Wire.beginTransmission(MAG_ADDR);
  Wire.write(i2creg);
  Wire.endTransmission();
  Wire.requestFrom(MAG_ADDR,1);
  return Wire.read();
}
