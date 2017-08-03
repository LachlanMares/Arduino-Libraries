#ifndef MATRIX2X2_h
#define MATRIX2X2_h

#include "Arduino.h"

class Matrix2x2
{
public:
        Matrix2x2();
        virtual ~Matrix2x2();

        inline void Copy2x2(float** A,float** B)
        {
            B[0][0] = A[0][0];
            B[0][1] = A[0][1];
            B[1][0] = A[1][0];
            B[1][1] = A[1][1];
        }

        inline void Zero2x2(float** A)
        {
            A[0][0] = 0.0f;
            A[0][1] = 0.0f;
            A[1][0] = 0.0f;
            A[1][1] = 0.0f;
        }

        inline void Eye2x2(float** A)
        {
            A[0][0] = 1.0f;
            A[0][1] = 0.0f;
            A[1][0] = 0.0f;
            A[1][1] = 1.0f;
        }

        inline void ScaledEye2x2(float** A,float S)
        {
            A[0][0] = S;
            A[0][1] = 0.0f;
            A[1][0] = 0.0f;
            A[1][1] = S;
        }

        inline void Scale3x3(float** A,float B)
        {
            A[0][0] *= B;
            A[0][1] *= B;
            A[1][0] *= B;
            A[1][1] *= B;
        }

        inline void ScaledCopy2x2(float** A,float B,float** Y)
        {
            Y[0][0] = A[0][0] * B;
            Y[0][1] = A[0][1] * B;
            Y[1][0] = A[1][0] * B;
            Y[1][1] = A[1][1] * B;
        }

        inline void Add2x2(float** A,float** B,float** Y)
        {
            Y[0][0] = A[0][0] + B[0][0];
            Y[0][1] = A[0][1] + B[0][1];
            Y[1][0] = A[1][0] + B[1][0];
            Y[1][1] = A[1][1] + B[1][1];
        }

        inline void Subtract2x2(float** A,float** B,float** Y)
        {
            Y[0][0] = A[0][0] - B[0][0];
            Y[0][1] = A[0][1] - B[0][1];
            Y[1][0] = A[1][0] - B[1][0];
            Y[1][1] = A[1][1] - B[1][1];
        }

        inline void TransposeCopy2x2(float** A,float** Y)
        {
            Y[0][0] = A[0][0];
            Y[0][1] = A[1][0];
            Y[1][0] = A[0][1];
            Y[1][1] = A[1][1];
        }

        inline float Determinant2x2(float** A)
        {
            return 1.0f/(A[0][0]*A[1][1] - A[0][1]*A[1][0]);
        }

        inline void Diag2x2(float** A,float a,float b)
        {
            A[0][0] = a;
            A[0][1] = 0.0f;
            A[1][0] = 0.0f;
            A[1][1] = b;
        }

        void Transpose2x2(float**);
        void Multiply2x2(float**,float**,float**);
        void VectorMultiply2x2(float**,float*,float*);
        bool Invert2x2(float**,float**);

private:

};

#endif


