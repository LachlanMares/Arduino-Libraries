#include "MATRIX2X2.h"

Matrix2x2::Matrix2x2()
{
    //ctor
}

Matrix2x2::~Matrix2x2()
{
    //dtor
}

void Matrix2x2::Transpose2x2(float** A)
{
    float A01 = A[0][1];

    A[0][1] = A[1][0];
    A[1][0] = A01;
}

void Matrix2x2::Multiply2x2(float** A,float** B,float** Y)
{
    Y[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0];
    Y[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1];
    Y[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0];
    Y[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1];
}

void Matrix2x2::VectorMultiply2x2(float** A,float* B,float* Y)
{
    Y[0] = A[0][0]*B[0] + A[0][1]*B[1];
    Y[1] = A[1][0]*B[0] + A[1][1]*B[1];
}

bool Matrix2x2::Invert2x2(float** A,float** Y)
{
  float det = A[0][0]*A[1][1] - A[0][1]*A[1][0];

  if(det==0.0f)
  {
      return false;
  } else
    {
        Y[0][0] =  A[1][1]/det;
        Y[0][1] = -A[0][1]/det;
        Y[1][0] = -A[1][0]/det;
        Y[1][1] =  A[0][0]/det;
        return true;
    }
}
