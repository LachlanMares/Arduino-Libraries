#include "Butterworth.h"	

Butterworth::Butterworth(){

 }

void Butterworth::Init(float SampleFreq,float CutoffFreq,float InitVal){
  float _Wc = TWO_M_PI*CutoffFreq;
  float _c = 1.0f/(tan((_Wc*(1.0f/SampleFreq))/2.0f));
  float _G = _c*_c + SQRT2*_c + 1.0f;
  
  _Yc[0] = (2.0f - 2.0f*_c*_c)/_G;
  _Yc[1] = (_c*_c - SQRT2*_c + 1.0f)/_G;
  _Xc[0] = 1.0f/_G;
  _Xc[1] = 2.0f/_G;
  _Xc[2] = 1.0f/_G;
  
  for(int _i=0;_i<3;_i++){
    _x[_i] = InitVal;
    _y[_i] = InitVal;
  }
}

float Butterworth::UpdateFilter(float NewReading){
  _x[2] = _x[1];
  _x[1] = _x[0];
  _x[0] = NewReading;
  _y[2] = _y[1];
  _y[1] = _y[0]; 
  _y[0] = _Xc[0]*_x[0] + _Xc[1]*_x[1] + _Xc[2]*_x[2] - _Yc[0]*_y[1] - _Yc[1]*_y[2];
  return _y[0];
}

float Butterworth::Output(){
  return _y[0];
}
