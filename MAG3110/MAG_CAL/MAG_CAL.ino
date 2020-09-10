
#include <Wire.h>
#include <math.h>
#include <MsTimer2.h>

// System constants
#define TO_RAD(x)        (x * 0.01745329252)  // *pi/180
#define TO_DEG(x)        (x * 57.2957795131)  // *180/pi
#define IntPeriod        125
#define Dt               IntPeriod/1000.0f
#define phi              0
#define theta            1
#define psi              2
#define EMagX            28.621f                                          // X axis earth magnetic field strength uT
#define EMagY            0.0f
#define EMagZ            -44.815f
#define Mag_Theta        TO_RAD(-45)


typedef struct vector_struct {
float x;
float y;
float z;
} Vector;

typedef struct vectorI_struct {
int x;
int y;
int z;
} VectorI;

typedef struct quaternion_struct {
float w;
float x;
float y;
float z;
} Quarternion;

typedef struct caibration_struct {
float Xmax;
float Xmin;
float Xbias;
float Xscale;
float Ymax;
float Ymin;
float Ybias;
float Yscale;
float Zmax;
float Zmin;
float Zbias;
float Zscale;
} CalibrationMatrix;

Vector Mag;
Vector RawMag;
Vector NormMag;
Vector EarthMag;
CalibrationMatrix MagC;

// Global system variables
boolean CalFlag = true; 
boolean UpdateFlag = false;
float euler[3] = {0.0,0.0,0.0};
float CosTheta = cos(Mag_Theta);
float SinTheta = sin(Mag_Theta);
float SinTheta_n = -1.0f*SinTheta;
int printcounter = 0;

void setup(){
  Serial.begin(57600);
  Wire.begin();
  FastI2C();
  InitStructs();
  HMCInit();
  MsTimer2::set(IntPeriod,InterruptRoutine);
  MsTimer2::start();
}

void loop(){
  if (CalFlag == true){
    CalibrateMag();
  }
  if(UpdateFlag){
    UpdateFlag = false;
    HMCRead();
    printdata();
  }
}





