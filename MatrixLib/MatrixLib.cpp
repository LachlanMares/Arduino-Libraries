#include "MatrixLib.h"

MatrixLib::MatrixLib() : Matrix2x2(),Matrix3x3(),Matrix4x4()
{
    //ctor
}

MatrixLib::~MatrixLib()
{
    //dtor
}

void MatrixLib::Copy(float** A,float** B,int r,int c)
{
    for (int i=0;i<r;i++)
    {
        for (int j=0;j<c;j++)
        {
          B[i][j] = A[i][j];
        }
    }
}

void MatrixLib::Zero(float** A,int r,int c)
{
    for (int i=0;i<r;i++)
    {
        for (int j=0;j<c;j++)
        {
            A[i][j] = 0.0f;
        }
    }
}

void MatrixLib::Eye(float** A,int k)
{
    for (int i=0;i<k;i++)
    {
        for (int j=0;j<k;j++)
        {
          A[i][j] = (i==j?1.0f:0.0f);
        }
    }
}

void MatrixLib::ScaledEye(float** A,float S,int k)
{
    for (int i=0;i<k;i++)
    {
        for (int j=0;j<k;j++)
        {
          A[i][j] = (i==j?S:0.0f);
        }
    }
}

void MatrixLib::Scale(float** A,float B,int r,int c)
{
    for (int i=0;i<r;i++)
    {
        for (int j=0;j<c;j++)
        {
            A[i][j] *= B;
        }
    }
}

void MatrixLib::ScaledCopy(float** A,float B,float** Y,int r,int c)
{
    for (int i=0;i<r;i++)
    {
        for (int j=0;j<c;j++)
        {
            Y[i][j] = A[i][j] * B;
        }
    }
}

void MatrixLib::Add(float** A,float** B,float** Y,int r,int c)
{
    for (int i=0;i<r;i++)
    {
        for (int j=0;j<c;j++)
        {
            Y[i][j] = A[i][j] + B[i][j];
        }
    }
}

void MatrixLib::Subtract(float** A,float** B,float** Y,int r,int c)
{
    for (int i=0;i<r;i++)
    {
        for (int j=0;j<c;j++)
        {
            Y[i][j] = A[i][j] - B[i][j];
        }
    }
}

void MatrixLib::TransposeCopy(float** A,float** Y,int k)
{
    for (int i=0;i<k;i++)
    {
        for (int j=0;j<k;j++)
        {
            Y[j][i] = A[i][j];
        }
    }
}

void MatrixLib::Transpose(float** A,int k)
{
    float** B = new float*[k];
    for (int i=0;i<k;i++)
    {
        B[i] = new float[k];
    }

    TransposeCopy(A,B,k);
    Copy(B,A,k,k);

    for(int i=0;i<k;i++)
    {
        delete [] B[i];
    }
    delete [] B;
}

void MatrixLib::MultiplySquare(float** A,float** B,float** Y,int k)
{
    Zero(Y,k,k);

    for (int i=0;i<k;i++)
    {
        for (int j=0;j<k;j++)
        {
            for(int l=0;l<k;l++)
            {
                Y[i][j] += A[i][l] * B[l][j];
            }
        }
    }
}

bool MatrixLib::Multiply(float** A,float** B,float** Y,int r1,int c1,int r2,int c2)
{
    bool _ret = false;
    if (c1==r2)
    {
        for (int i=0;i<r1;i++)
        {
            for (int j=0;j<c2;j++)
            {
                Y[i][j] =  0.0f;
                for(int l=0;l<c1;l++)
                {
                    Y[i][j] += A[i][l] * B[l][j];
                }
            }
        }
    }
    return _ret;
}

void MatrixLib::VectorMultiply(float** A,float* B,float* Y,int k)
{

    for (int i=0;i<k;i++)
    {
        Y[i] = 0.0f;
        for (int j=0;j<k;j++)
        {
            Y[i] += A[i][j] * B[j];
        }
    }
}

float MatrixLib::Determinant(float** A,int k)
{
    float** B = new float*[k];
    float s=1,det=0;
    int i,j,m,n,c;

    for (i=0;i<k;i++)
    {
        B[i] = new float[k];
    }

    if (k==1)
    {
        delete B[0];
        delete B;
        return (A[0][0]);
    } else
      {
        det = 0;
        for (c=0;c<k;c++)
        {
            m = 0;
            n = 0;
            for (i=0;i<k;i++)
            {
                for (j=0;j<k;j++)
                {
                    B[i][j]=0;
                    if (i!=0&&j!=c)
                    {
                        B[m][n]=A[i][j];
                        if (n<(k-2))
                        {
                            n++;
                        } else
                          {
                            n=0;
                            m++;
                          }
                    }
                }
            }
            det = det + s*(A[0][c]*Determinant(B,k-1));
            s = -1*s;
        }
      }

    for (i=0;i<k;i++)
    {
        delete B[i];
    }
    delete B;
    return det;
}

bool MatrixLib::Inverse(float** A,float** Y,int f)
{
    bool _ret = false;
    int p,q,m,n,i,j;
    float det;
    float** B = new float*[f];
    float** F = new float*[f];

    for (i=0;i<f;i++)
    {
        B[i] = new float[f];
        F[i] = new float[f];
    }

    det = Determinant(A,f);

    if (det!=0.0f)
    {
        for (q=0;q<f;q++)
        {
            for (p=0;p<f;p++)
            {
                m = 0;
                n = 0;
                for (i=0;i<f;i++)
                {
                    for (j=0;j<f;j++)
                    {
                        B[i][j]=0;
                        if (i!=q&&j!=p)
                        {
                            B[m][n]=A[i][j];
                            if (n<(f-2))
                            {
                                n++;
                            }   else
                                {
                                    n=0;
                                    m++;
                                }
                        }
                    }
                }
                F[q][p]=pow(-1,q+p)*Determinant(B,f-1);
            }
        }

        for (i=0;i<f;i++)
        {
            for (j=0;j<f;j++)
            {
                Y[i][j] = F[j][i]/det;
            }
        }
        _ret = true;
    }

    for (i=0;i<f;i++)
    {
        delete B[i];
        delete F[i];
    }
    delete B;
    delete F;
    return _ret;
}
