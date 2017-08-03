#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#include "Arduino.h"

#include <Math.h>
#include <Matrix2x2.h>
#include <Matrix3x3.h>
#include <Matrix4x4.h>

class MatrixLib: public Matrix2x2, public Matrix3x3, public Matrix4x4
{
    public:
        MatrixLib();
        virtual ~MatrixLib();
        void Copy(float**,float**,int,int);
        void Zero(float**,int,int);
        void Eye(float**,int);
        void ScaledEye(float**,float,int);
        void Scale(float**,float,float**,int,int);
        void ScaledCopy(float**,float,int,int);
        void Add(float**,float**,float**,int,int);
        void Subtract(float**,float**,float**,int,int);
        void TransposeCopy(float**,float**,int);
        void Transpose(float**,int);
        void MultiplySquare(float**,float**,float**,int);
        bool Multiply(float**,float**,float**,int,int,int,int);
        void VectorMultiply(float**,float*,float*,int);
        float Determinant(float**,int);
        bool Inverse(float**,float**,int);

    protected:
    private:
};

#endif // MATRIXLIB_H
