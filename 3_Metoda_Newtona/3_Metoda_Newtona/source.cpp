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

bool solveEquation2D(const double* coeffs, double* solution)
{
    if (coeffs[0] != 0)
    {
        double a, b; // zmienne pomocnicze
        a = -coeffs[3]/coeffs[0];
        if((b = coeffs[1] * a + coeffs[5]) == 0)
            return false;
        solution[1] = (coeffs[2]*a + coeffs[5]) / b;
        solution[0] = (coeffs[2] - solution[1]*coeffs[1]) / coeffs[0];
        return true;
    }
    else if (coeffs[1] != 0)
    {
        solution[1] = coeffs[2]/coeffs[1];
        if(coeffs[4] == 0)
            return false;
        solution[0] = (coeffs[5] - solution[1]*coeffs[4]) / coeffs[4];
        return true;
    }
    else
        return false;
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
    double* solutions = new double[3];
    double* fx = new double[2];
    double* prev = new double[2];
    double* Df = new double[6];

    for (int i = 1; i <= k; ++i)
    {
        x[2] += h;
        do
        {
            f(x, fx, Df);
            Df[2] = -fx[0];
            Df[5] = -fx[1];
            solutions[0] -= fx[0]*
        } while(inAbsErr( max2(fx[0],fx[1]) ));
    }

    int error_on_index = -1;

    //...

    if (error_on_index != -1)
        return error_on_index;

    for(int i=1; i<=k; ++i)
        std::cout << x[2] + i*h << '\n';

    return 0;
}