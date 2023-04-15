// Szymon Ciula

#include "source.h"

void printVector(const double* x, unsigned N)
{
    for(unsigned i=0;i<N;++i)
        printf("%17.17f ",x[i]);
    printf("\n");
}

void swap(double& a, double& b)
{
    double temp = a;
    a = b;
    b = temp;
}

bool reverseMatrix2D(double* A)
{
    double det = A[0]*A[3] - A[1]*A[2];
    if (det != 0)
    {
        det = 1/det;
        A[3] = det*A[3];
        A[1] = -det*A[1];
        A[2] = -det*A[2];
        A[0] = det*A[0];
        swap(A[0],A[3]);
        return true;
    }
    return false;
}

void multiplyMatrix(const double* A, const double* B, double* C)
{
    C[0] = A[0]*B[0] + A[1]*B[1];
    C[1] = A[2]*B[0] + A[3]*B[1];
}

int findCurve(FuncPointer f, double* x, unsigned k, double h)
{
    unsigned iter;
    double solutions[3];
    double fx[2];
    double prev;
    double Df[6];
    double C[2];

    solutions[2] = x[2];
    for (unsigned i = 1; i <= k; ++i)
    {
        solutions[0] = x[0];
        solutions[1] = x[1];
        solutions[2] += h;
        f(solutions, fx, Df);
        prev = max2(abso(fx[0]),abso(fx[1]));
        iter = 0;
        do
        {
            Df[2] = Df[3];
            Df[3] = Df[4];
            if (reverseMatrix2D(Df))
            {
                multiplyMatrix(Df,fx,C);
                solutions[0] -= C[0];
                solutions[1] -= C[1];
                f(solutions, fx, Df);

                if (++iter == checkIter)
                {
                    if ( max2(abso(fx[0]), abso(fx[1]))  >  prev )
                        return i;
                    prev = max2(abso(fx[0]), abso(fx[1]));
                    iter = 0;
                }
            }
            else
                return i;
        } while( !(inAbsErr( max2(abso(fx[0]), abso(fx[1])) )) );

        printVector(solutions, 3);
    }

    return 0;
}

int findSurface(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2)
{
    unsigned iter;
    double prev;
    double solutions[3];
    double fx[1];
    double Df[3];

    solutions[1] = x[1];
    for (unsigned i = 1; i <= k1; ++i)
    {
        solutions[1] += h1;
        solutions[2] = x[2];
        for (unsigned j = 1; j <= k2; ++j)
        {
            solutions[0] = x[0];
            solutions[2] += h2;
            f(solutions, fx, Df);
            iter = 0;
            prev = *fx;
            do
            {
                if (Df[0] != 0)
                {
                    solutions[0] -= *fx / Df[0];
                    f(solutions, fx, Df);

                    if (++iter == checkIter)
                    {
                        if ( *fx > prev )
                            return i*k1+j;
                        prev = *fx;
                        iter = 0;
                    }
                }
                else
                    return i*k1+j;
            } while( !(inAbsErr( *fx )));

            printVector(solutions, 3);
        }
        printf("\n");
    }

    return 0;
}

int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2)
{
    unsigned iter;
    double prev;
    double solutions[4];
    double fx[2];
    double Df[8];
    double C[2];

    solutions[2] = x[2];
    for (unsigned i = 1; i <= k1; ++i)
    {
        solutions[2] += h1;
        solutions[3] = x[3];
        for (unsigned j = 1; j <= k2; ++j)
        {
            solutions[0] = x[0];
            solutions[1] = x[1];
            solutions[3] += h2;
            f(solutions, fx, Df);
            // Modyfikujemy, bo szukamy punktu stalego.
            Df[0] -= 1.;
            Df[5] -= 1.;
            fx[0] -= solutions[0];
            fx[1] -= solutions[1];

            iter = 0;
            prev = max2(abso(fx[0]), abso(fx[1]));
            do
            {
                Df[2] = Df[4];
                Df[3] = Df[5];
                if (reverseMatrix2D(Df))
                {
                    multiplyMatrix(Df,fx,C);
                    solutions[0] -= C[0];
                    solutions[1] -= C[1];
                    f(solutions, fx, Df);

                    Df[0] -= 1.;
                    Df[5] -= 1.;
                    fx[0] -= solutions[0];
                    fx[1] -= solutions[1];

                    if (++iter == checkIter)
                    {
                        if ( max2(abso(fx[0]), abso(fx[1])) > prev )
                            return i*k1+j;
                        prev = max2(abso(fx[0]), abso(fx[1]));
                        iter = 0;
                    }
                }
                else
                    return i*k1+j;
            } while( !(inAbsErr(max2(abso(fx[0]), abso(fx[1])))) );

            printVector(solutions, 4);
        }
        printf("\n");
    }

    return 0;
}
