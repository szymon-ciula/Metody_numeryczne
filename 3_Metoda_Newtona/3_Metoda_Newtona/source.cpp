// Szymon Ciula

#include <cstdio>
#include <iostream>
#include "source.h"

using namespace std;

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

/*
    A - 2x2
    B - 2x1
*/
void multiplyMatrix(const double* A, const double* B, double* C)
{
    C[0] = A[0]*B[0] + A[1]*B[1];
    C[1] = A[2]*B[0] + A[3]*B[1];
}

/*
    Funkcja ma obliczyc i wydrukowac na ekran wybrane punkty x1,x2,...,xk spelniajace rownanie:     f(xi)=(f1(xi),f2(xi))=(0,0)
    z dokladnoscia co najmniej max(|fi(xi)|,|f2(xi)|) <= 10e-14.
    
    Przy ustalonej wartosci zmiennej c jest to funkcja fc:R2 ->R2, ktorej miejsca zerowe mozemy wyliczac metoda Newtona.
    Zadaniem jest obliczenie i wydrukowanie na ekran miejsc zerowych fc oraz wartosci parametru c dla c rownych kolejno:
      x[2]+h, x[2]+2*h, ..., x[2]+k*h.

    @param
    f - wskaznik do funkcji R3 -> R2
    x - tablica liczb double dlugosci 3, zawierajaca punkt poczatkowy bliski miejsca zerowego funkcji (czyli f(x)~=(0,0))
    k - okresla liczbe punktow do wyznaczenia
    h - krok zmiany parametru. Funkcje f mozemy traktowac jako:     f(a,b,c) = (f1(a,b,c),f2(a,b,c))

    @return
    jesli dla pewnego i=1,...,k nie uda sie wyznaczyc zera funkcji dla c=x[2]+i*h i z tolerancja absolutna 10e-14 (na przyklad metoda numeryczna bedzie rozbiezna),
    to nalezy zakonczyc dzialanie funkcji bez wypisywania blednego miejsca zerowego i zwrocic indeks i, dla ktorego nastapil problem.
    W przeciwnym przypadku zwracamy wartosc 0 oznaczajaca brak bledu.
*/
int findCurve(FuncPointer f, double* x, unsigned k, double h)
{
    double solutions[3];
    double fx[2];
    double Df[6];
    double C[2];

    solutions[2] = x[2];
    for (int i = 1; i <= k; ++i)
    {
        solutions[0] = x[0];
        solutions[1] = x[1];
        solutions[2] += h;
        f(solutions, fx, Df);
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
            }
            else
                return i;
        } while( !(inAbsErr( max2(fx[0],fx[1]) )) );

        printVector(solutions, 3);
    }

    return 0;
}