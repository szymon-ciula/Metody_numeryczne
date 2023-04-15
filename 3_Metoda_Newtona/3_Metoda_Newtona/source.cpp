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

void multiplyMatrix(const double* A, const double* B, double* C)
{
    C[0] = A[0]*B[0] + A[1]*B[1];
    C[1] = A[2]*B[0] + A[3]*B[1];
}

int findCurve(FuncPointer f, double* x, unsigned k, double h)
{
    double solutions[3];
    double fx[2];
    double Df[6];
    double C[2];

    solutions[2] = x[2];
    for (unsigned i = 1; i <= k; ++i)
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

int findSurface(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2)
{
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
            do
            {
                if (Df[0] != 0)
                {
                    solutions[0] -= *fx / Df[0];
                    f(solutions, fx, Df);
                }
                else
                    return i*k1+j;
            } while( !(inAbsErr( *fx )) );

            printVector(solutions, 3);
        }
        printf("\n");
    }

    return 0;
}

/*
    W tej funkcji zakladamy, ze f:R4 -> R2. Nazwijmy zmienne funkcji f kolejno x,y,a,b.
    Przy ustalonej wartosci ostatnich dwoch zmiennych a,b jest to funkcja fa,b:R2 ->R2, ktora moze miec izolowany punkt staly.
    Zadaniem jest obliczenie i wydrukowanie wektorow (x,y,a,b), dla ktorych f(x,y,a,b) = fa,b(x,y)=(x,y) z dokladnoscia |fa,b(x,y)-(x,y)|<=10e-14 w normie maximum.

    Argumentami funkcji findFixedPoints sa
    f - wskaznik do funkcji R4 -> R2
    x - tablica liczb double dlugosci 4, zawierajaca punkt poczatkowy spelniajacy warunek f(x[0],x[1],x[2],x[3])~=(x[0],x[1]))
    k1,k2 - okreslaja liczby punktow do wyznaczenia
    h1,h2 - kroki zmiany parametrow.
    
    Zadaniem jest obliczenie i wydrukowanie na ekran punktow stalych fa,b wraz z wartosciami a,b dla (a,b) kolejno rownych
      (x[2]+h1,x[3]+h2)
      (x[2]+h1,x[3]+2*h2)
      ...
      (x[2]+h1,x[3]+k2*h2)
      (x[2]+2*h1,x[3]+h2)
      (x[2]+2*h1,x[3]+2*h2)
      ...
      (x[2]+2*h1,x[3]+k2*h2)
      ...
      (x[2]+k1*h1,x[3]+h2)
      (x[2]+k1*h1,x[3]+2*h2)
       ...
      (x[2]+k1*h1,x[3]+k2*h2)
      

    Dodatkowo, dla wiekszej czytelnosci wyjscia, po kazdym zestawie punktow z ustalona wartoscia b wstawiamy wolna linie. 

    @return
    jesli dla pewnego i=1,...,k1, j=1,...,k2 nie uda sie wyznaczyc punktu stalego funkcji fa,b dla parametrow a=x[2]+i*h1, b=x[3]+j*h2 z tolerancja absolutna 10e-14,
    to nalezy zakonczyc dzialanie funkcji bez wypisywania blednego punktu stalego i zwrocic wartosc i*k1+j.
    W przeciwnym przypadku zwracamy wartosc 0 oznaczajaca brak bledu.
*/
int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2)
{
    double solutions[4];
    double fx[2];
    double Df[8];
    double C[2];

    solutions[2] = x[2];
    for (unsigned i = 1; i <= k1; ++i)
    {
        cout << "i=" << i << endl;
        solutions[2] += h1;
        solutions[3] = x[3];
        for (unsigned j = 1; j <= k2; ++j)
        {
            cout << "\tj=" << j << endl;
            solutions[0] = x[0];
            solutions[1] = x[1];
            solutions[3] += h2;
            f(solutions, fx, Df);
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
                }
                else
                    return i*k1+j;
            } while( !(inAbsErr( max2(fx[0]-solutions[0], fx[1]-solutions[1]))));

            printVector(solutions, 4);
        }
        printf("\n");
    }

    return 0;
}
