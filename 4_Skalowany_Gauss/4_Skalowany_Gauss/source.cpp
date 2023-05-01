// Szymon Ciula
#include "source.h"
#include "vectalg.h"

void swap(double& a, double& b)
{
    double temp = a;
    a = b;
    b = temp;
}

Vector& operator+=(Vector& a, const Vector& b)
{
    for(size_t i=0; i<a.size(); ++i)
        a[i] += b[i];
    return a;
}

Vector solveEquations(const Matrix& A0, const Vector& b, double  eps)
{
    const size_t N = b.size();
    Matrix A(A0);
    Vector S(N), scales(N);
    Vector B(b);
    Vector X(N);

    for(size_t i=0; i<N; ++i)
        X[i] = 0;

    double temp; // zmienna pomocnicza
    size_t idx; // Zmienna potrzebna do zamiany kolumn przy wyborze elementu glownego.

    // Obliczamy norme maksimum kazdego wiersza.
    for (size_t i = 0; i < N; ++i)
    {
        temp = 0;
        for (size_t j = 0; j < N; ++j)
            temp = max(abso(A0(i, j)), abso(temp));
        scales[i] = temp;
    }

    do
    {
        S = scales;
        A = A0;
        // Algorytm Gaussa
        for (size_t i = 0; i < N - 1; ++i)
        {
            // Wybieramy element glowny.
            idx = i;
            for (size_t k = i + 1; k < N; ++k)
            {
                if (abso(A(idx, i)) * S[k] < abso(A(k, i)) * S[idx])
                    idx = k;
            }
            // Zamieniamy wiersze, aby usadowic element glowny w odpowiednim miejscu.
            if (i != idx)
            {
                swap(S[i], S[idx]);
                swap(B[i], B[idx]);
                for (size_t k = i; k < N; ++k)
                    swap(A(i, k), A(idx, k));
            }
            // Zerujemy kolumne pod elementem glownym podmacierzy.
            for (size_t j = i + 1; j < N; ++j)
            {
                temp = A(j, i) / A(i, i);
                A(j, i) = 0;
                for (size_t k = i + 1; k < N; ++k)
                    A(j, k) -= A(i, k) * temp;
                B[j] -= B[i] * temp;
            }
        }

        // Rozwiazujemy uklad rownan zadany przez macierz gornotrojkotna.
        for (int i = N - 1; i >= 0; --i)
        {
            temp = 0;
            for (int j = N - 1; j > i; --j)
                temp += A(i, j) * B[j];
            B[i] = (B[i] - temp) / A(i, i);
        }
        X += B;
    } while ((B = residual_vector(A0, b, X)).max_norm()  >=  eps);


    return X;
}

