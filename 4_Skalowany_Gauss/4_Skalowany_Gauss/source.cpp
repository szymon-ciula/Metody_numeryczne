// Szymon Ciula
#include "vectalg.h"
#include "source.h"

//inline double abso(double x) { return x>=0 ? x : -x; }
//inline double max(double a, double b) { return a>=b ? a : b; }

void swap(double& a, double& b)
{
    double temp = a;
    a = b;
    b = temp;
}

Vector solveEquations(const Matrix & A0, const Vector & b, double  eps)
{
    const size_t N = b.size();
    Matrix A = A0;
    double* S = new double[N];

    // Obliczamy norme kazdego wiersza.
    double maxx;
    for (size_t i = 0; i < N; ++i)
    {
        maxx = A(i,0);
        for (size_t j = 1; j < N; ++j)
            maxx = max(A(i,j), maxx);
        S[i] = maxx;
    }

    
    size_t idx;
    short sign = 1;
    double a;
    for (size_t i = 0; i < N; ++i)
    {
        // Wybieramy element glowny.
        idx = i;
        maxx = A(i,i)/S[i];
        for (size_t k = i+1; k < N; ++k)
        {
            if (maxx < A(k, i) / S[k])
            {
                maxx = A(k, i) / S[k];
                idx = k;
            }
        }
        // Zamieniamy wiersze, aby usadowic element glowny w odpowiednim miejscu.
        if (i != idx)
        {
            sign *= -1;
            swap(S[i],S[idx]);
            for(size_t k = i; k < N; ++k)
                swap(A(i,k), A(idx,k));
        }

        for (size_t j = i+1; j < N; ++j)
        {
            a = A(j,i)/A(i,i);
            A(j,i) = 0;
            for (size_t k = i+1; k < N; ++k)
                A(j,k) -= A(i,k)*a;
        }
    }

    std::cout << A;

    return b;
}


