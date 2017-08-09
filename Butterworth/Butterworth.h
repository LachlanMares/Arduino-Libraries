#ifndef Butterworth_h
#define Butterworth_h
#include "Arduino.h"

#define M_PI                3.141592653589793238f               // Pi
#define TWO_M_PI            6.283185307179586477f               // Pi * 2
#define SQRT2               1.414213562373095048f               // Square root of 2 

class Butterworth
{
public:
	Butterworth();
        void Init(float,float,float);
        float UpdateFilter(float);
        float Output();
private:
        float _x[3],_y[3],_Xc[3],_Yc[3];
};

#endif
