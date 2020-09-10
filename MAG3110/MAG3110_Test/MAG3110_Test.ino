#include <Wire.h>
#include <MAG3110.h>
//#include <MMA8491Q.h>



#define TO_DEG(x)        (x*57.2957795131)  // *180/pi
#define TO_RAD(x)        (x*0.01745329252)  // *pi/180
//#define MMAQ8491Q_PIN     8

calibrationparameters calpar = {-0.314241f,0.344893f,-0.202280f,3.415620f,0.039757f,-0.008708f,0.039757f,3.414763f,-0.013963f,-0.008708f,-0.013963f,3.438413f};

vector xaxis = {1.000,0.000,0.000};

vector mag = {0.000,0.000,0.000};
vector magsign = {1.000,1.000,1.000};

vector accl = {0.000,0.000,0.000};
vector acclsign = {1.000,1.000,1.000};

vector earth = {28.621f,0.000f,-44.815f};
vector euler = {0.000,0.000,0.000};

quarternion Q = {1.000,0.000,0.000,0.000}; 

MAG3110 magn(&mag,&magsign);
//MMA8491Q accel(&accl,&acclsign,MMAQ8491Q_PIN);

void setup() 
{
  Serial.begin(38400);
  Wire.begin();
  NormaliseVector(&earth);
  magn.SetCalibrationParameters(&calpar);
  magn.Start();
  magn.Mode(true);
}

void loop() 
{
  /*if(accel.Update())
  {
    //accel.Normalise(); 
    //QFromAccl(&accl,&euler);
    Serial.print("X = ");
    Serial.print(accl.x);
    Serial.print(" Y = ");
    Serial.print(accl.y);
    Serial.print(" Z = ");
    Serial.println(accl.z);
    delay(500);
 } */

  if(magn.Update())
  {
    //Gradient(&mag,&earth,&Q);
    //NormaliseQuarternion(&Q);
    //ConjugateQuarternion(&Q);
    //Serial.print(Q.w,2);
    //Serial.print('\t');
    //Serial.print(Q.x,2);
    //Serial.print('\t');
    //Serial.print(Q.y,2);
    //Serial.print('\t');
    //Serial.print(Q.z,2);
    //Serial.print('\t');
    //Serial.println(Q.w*Q.w + Q.x*Q.x + Q.y*Q.y + Q.z*Q.z,2);
    //EulerFromMag(&mag,&earth,&euler);
    //EulerFromMagNew(&mag,&earth,&euler);
    //Serial.print("Heading = "); 
    //Serial.println(QFromMag(&mag,&earth));
    //Serial.print("Euler = "); 
    //Serial.print(TO_DEG(euler.x));
    //Serial.print(" ");
    //Serial.print(TO_DEG(euler.z));
    //Serial.print(" ");
    //Serial.println(TO_DEG(atan2(-mag.y,mag.x)));
    //Serial.println(TO_DEG(euler.z));
    EulerAxisAngle(&earth,&xaxis,&euler);
    EulerAxisAngle(&euler,&mag,&euler);
    Serial.print(TO_DEG(euler.x));
    Serial.print('\t');
    Serial.print(TO_DEG(euler.y));
    Serial.print('\t');
    Serial.println(TO_DEG(euler.z));
    //Serial.print(TO_DEG(atan2(2.0*(Q.w*Q.x + Q.y*Q.z) , 1.0 - 2.0*(Q.x*Q.x + Q.y*Q.y))));
    //Serial.print('\t');
    //Serial.print(TO_DEG(asin(2.0*(Q.w*Q.y - Q.z*Q.x))));
    //Serial.print('\t');
    //Serial.println(TO_DEG(atan2(2.0*(Q.w*Q.z + Q.x*Q.y) , 1.0 - 2.0*(Q.y*Q.y + Q.z*Q.z))));
  }
}


