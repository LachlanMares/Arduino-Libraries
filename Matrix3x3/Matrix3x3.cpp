#include "MATRIX3X3.h"

Matrix3x3::Matrix3x3()
{
    //ctor
}

Matrix3x3::~Matrix3x3()
{
    //dtor
}

void Matrix3x3::Transpose3x3(float** A)
{
    float A01 = A[0][1];
    float A02 = A[0][2];
    float A12 = A[1][2];

    A[0][1] = A[1][0];
    A[0][2] = A[2][0];
    A[1][2] = A[2][1];
    A[1][0] = A01;
    A[2][0] = A02;
    A[2][1] = A12;
}

void Matrix3x3::Multiply3x3(float** A,float** B,float** Y)
{
    Y[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0] + A[0][2]*B[2][0];
    Y[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1] + A[0][2]*B[2][1];
    Y[0][2] = A[0][0]*B[0][2] + A[0][1]*B[1][2] + A[0][2]*B[2][2];

    Y[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0] + A[1][2]*B[2][0];
    Y[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1] + A[1][2]*B[2][1];
    Y[1][2] = A[1][0]*B[0][2] + A[1][1]*B[1][2] + A[1][2]*B[2][2];

    Y[2][0] = A[2][0]*B[0][0] + A[2][1]*B[1][0] + A[2][2]*B[2][0];
    Y[2][1] = A[2][0]*B[0][1] + A[2][1]*B[1][1] + A[2][2]*B[2][1];
    Y[2][2] = A[2][0]*B[0][2] + A[2][1]*B[1][2] + A[2][2]*B[2][2];
}

void Matrix3x3::VectorMultiply3x3(float** A,float* B,float* Y)
{
    Y[0] = A[0][0]*B[0] + A[0][1]*B[1] + A[0][2]*B[2];
    Y[1] = A[1][0]*B[0] + A[1][1]*B[1] + A[1][2]*B[2];
    Y[2] = A[2][0]*B[0] + A[2][1]*B[1] + A[2][2]*B[2];
}

bool Matrix3x3::Invert3x3(float** A,float** Y)
{
  float B[3][3],det;

  // Cofactor & Transpose

  B[0][0] =   A[1][1]*A[2][2] - A[1][2]*A[2][1];
  B[1][0] = -(A[1][0]*A[2][2] - A[1][2]*A[2][0]);     // Cofactor for B[0][1] transposed
  B[2][0] =   A[1][0]*A[2][1] - A[1][1]*A[2][0];      // Cofactor for B[0][2] transposed

  B[0][1] = -(A[0][1]*A[2][2] - A[0][2]*A[2][1]);     // Cofactor for B[1][0] transposed
  B[1][1] =   A[0][0]*A[2][2] - A[0][2]*A[2][0];
  B[2][1] = -(A[0][0]*A[2][1] - A[0][1]*A[2][0]);     // Cofactor for B[1][2] transposed

  B[0][2] =   A[0][1]*A[1][2] - A[0][2]*A[1][1];      // Cofactor for B[2][0] transposed
  B[1][2] = -(A[0][0]*A[1][2] - A[0][2]*A[1][0]);     // Cofactor for B[2][1] transposed
  B[2][2] =   A[0][0]*A[1][1] - A[0][1]*A[1][0];

  // Calculate Determinant (Using Pre Transposed Cofactors)

  det = A[0][0]*B[0][0] + A[0][1]*B[1][0] + A[0][2]*B[2][0];

  if(det==0.0f)
  {
      return false;
  } else
    {
        Y[0][0] = B[0][0]/det;
        Y[0][1] = B[0][1]/det;
        Y[0][2] = B[0][2]/det;
        Y[1][0] = B[1][0]/det;
        Y[1][1] = B[1][1]/det;
        Y[1][2] = B[1][2]/det;
        Y[2][0] = B[2][0]/det;
        Y[2][1] = B[2][1]/det;
        Y[2][2] = B[2][2]/det;
        return true;
    }
}

float Matrix3x3::Determinant3x3(float** A)
{
  float B[3];

  // Cofactor

  B[0] =   A[1][1]*A[2][2] - A[1][2]*A[2][1];
  B[1] = -(A[1][0]*A[2][2] - A[1][2]*A[2][0]);
  B[2] =   A[1][0]*A[2][1] - A[1][1]*A[2][0];

  // Calculate Determinant

  return (A[0][0]*B[0] + A[0][1]*B[1] + A[0][2]*B[2]);
}
