#ifndef MATRIX3X3_h
#define MATRIX3X3_h

#include "Arduino.h"

class Matrix3x3
{
public:
        Matrix3x3();
        virtual ~Matrix3x3();

        inline void Copy3x3(float** A,float** Y)
        {
            Y[0][0] = A[0][0];
            Y[0][1] = A[0][1];
            Y[0][2] = A[0][2];
            Y[1][0] = A[1][0];
            Y[1][1] = A[1][1];
            Y[1][2] = A[1][2];
            Y[2][0] = A[2][0];
            Y[2][1] = A[2][1];
            Y[2][2] = A[2][2];
        }

        inline void Zero3x3(float** A)
        {
            A[0][0] = 0.0f;
            A[0][1] = 0.0f;
            A[0][2] = 0.0f;
            A[1][0] = 0.0f;
            A[1][1] = 0.0f;
            A[1][2] = 0.0f;
            A[2][0] = 0.0f;
            A[2][1] = 0.0f;
            A[2][2] = 0.0f;
        }

        inline void Eye3x3(float** A)
        {
            A[0][0] = 1.0f;
            A[0][1] = 0.0f;
            A[0][2] = 0.0f;
            A[1][0] = 0.0f;
            A[1][1] = 1.0f;
            A[1][2] = 0.0f;
            A[2][0] = 0.0f;
            A[2][1] = 0.0f;
            A[2][2] = 1.0f;
        }

        inline void ScaledEye3x3(float** A,float S)
        {
            A[0][0] = S;
            A[0][1] = 0.0f;
            A[0][2] = 0.0f;
            A[1][0] = 0.0f;
            A[1][1] = S;
            A[1][2] = 0.0f;
            A[2][0] = 0.0f;
            A[2][1] = 0.0f;
            A[2][2] = S;
        }

        inline void Scale3x3(float** A,float B)
        {
            A[0][0] *= B;
            A[0][1] *= B;
            A[0][2] *= B;

            A[1][0] *= B;
            A[1][1] *= B;
            A[1][2] *= B;

            A[2][0] *= B;
            A[2][1] *= B;
            A[2][2] *= B;
        }

        inline void ScaledCopy3x3(float** A,float B,float** Y)
        {
            Y[0][0] = A[0][0]*B;
            Y[0][1] = A[0][1]*B;
            Y[0][2] = A[0][2]*B;

            Y[1][0] = A[1][0]*B;
            Y[1][1] = A[1][1]*B;
            Y[1][2] = A[1][2]*B;

            Y[2][0] = A[2][0]*B;
            Y[2][1] = A[2][1]*B;
            Y[2][2] = A[2][2]*B;
        }

        inline void Add3x3(float** A,float** B,float** Y)
        {
            Y[0][0] = A[0][0] + B[0][0];
            Y[0][1] = A[0][1] + B[0][1];
            Y[0][2] = A[0][2] + B[0][2];
            Y[1][0] = A[1][0] + B[1][0];
            Y[1][1] = A[1][1] + B[1][1];
            Y[1][2] = A[1][2] + B[1][2];
            Y[2][0] = A[2][0] + B[2][0];
            Y[2][1] = A[2][1] + B[2][1];
            Y[2][2] = A[2][2] + B[2][2];
        }

        inline void Subtract3x3(float** A,float** B,float** Y)
        {
            Y[0][0] = A[0][0] - B[0][0];
            Y[0][1] = A[0][1] - B[0][1];
            Y[0][2] = A[0][2] - B[0][2];
            Y[1][0] = A[1][0] - B[1][0];
            Y[1][1] = A[1][1] - B[1][1];
            Y[1][2] = A[1][2] - B[1][2];
            Y[2][0] = A[2][0] - B[2][0];
            Y[2][1] = A[2][1] - B[2][1];
            Y[2][2] = A[2][2] - B[2][2];
        }

        inline void TransposeCopy3x3(float** A,float** Y)
        {
            Y[0][0] = A[0][0];
            Y[0][1] = A[1][0];
            Y[0][2] = A[2][0];
            Y[1][0] = A[0][1];
            Y[1][1] = A[1][1];
            Y[1][2] = A[2][1];
            Y[2][0] = A[0][2];
            Y[2][1] = A[1][2];
            Y[2][2] = A[2][2];
        }

        inline void Diag3x3(float** A,float a,float b,float c)
        {
            A[0][0] = a;
            A[0][1] = 0.0f;
            A[0][2] = 0.0f;
            A[1][0] = 0.0f;
            A[1][1] = b;
            A[1][2] = 0.0f;
            A[2][0] = 0.0f;
            A[2][1] = 0.0f;
            A[2][1] = c;
        }

        void Transpose3x3(float**);
        void Multiply3x3(float**,float**,float**);
        void VectorMultiply3x3(float**,float*,float*);
        bool Invert3x3(float**,float**);
        float Determinant3x3(float**);

private:

};

#endif

