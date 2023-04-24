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

Vector operator*(const Matrix& M, const Vector& V)
{
    Vector R(V.size());

    for (size_t i = 0; i < V.size(); ++i)
    {
        R[i] = M(i,0)*V[0];
        for(size_t j = 1; j < V.size(); ++j)
            R[i] += M(i,j)*V[j];
    }

    return R;
}

Matrix operator*(const Matrix& M, const Matrix& V)
{
    Matrix R(V.size());

    for (size_t i = 0; i < V.size(); ++i)
    {
        for (size_t j = 0; j < V.size(); ++j)
        {
            R(i,j) = M(i, 0) * V(0,j);
            for (size_t k = 1; k < V.size(); ++k)
                 R(i, j) += M(i, k) * V(k,j);
        }
    }

    return R;
}

void reverseTriangularUpMatrix(Matrix& M, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        M(i,i) = 1/M(i,i);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i+1; j < n; ++j)
        {
            M(i,j) = M(i,j)*M(i,i);
            for(size_t k = i+1; k < j; ++k)
                M(i,j) += M(k,j)*M(i,k);
            M(i,j) *= -M(j,j);
        }
    }
}

void reverseTriangularLowMatrix(Matrix& M, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        M(i,i) = 1/M(i,i);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i+1; j < n; ++j)
        {
            M(i,j) = M(i,j)*M(j,j);
            for(size_t k = j+1; k < i; ++k)
                M(i,j) += M(k,j)*M(i,k);
            M(i,j) *= -M(i,i);
        }
    }
}

Vector operator-(const Vector& a, const Vector& b)
{
    Vector v(a.size());
    for(size_t i=0; i<a.size(); ++i)
        v[i] = a[i]-b[i];
    return v;
}

Vector solveEquations(const Matrix & A0, const Vector & b, double  eps)
{
    const size_t N = b.size();
    Matrix A = A0;
    Vector S(N);

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

    std::cout << A << std::endl;

    reverseTriangularLowMatrix(A, N);
    //Vector v(A * b);
    std::cout << A;// << std::endl <<  A*A0 << std::endl << A0*v << std::endl << b << std::endl << std::endl;
    //Vector r(b-A*v);
    //std::cout << residual_vector(A,b,v);


    return b;
}


