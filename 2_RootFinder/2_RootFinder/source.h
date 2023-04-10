#pragma once

double abso(double x) { return (x<0 ? -x : x); }
short sgn(double x) { return x<0 ? -1 : 1; }
bool inDelta(double a, double b, double delta) { return abso(b-a) < delta; }
bool inEps(double fx, double eps) { return abso(fx)<eps; }

void swap(double& a, double& b);

void bisection(
    double (*f)(double),    // funkcja kt�rej zera szukamy w [a, b] 
    double& a,              // lewy koniec przedzia�u
    double& b,              // prawy koniec przedzia�u
    double& fa,             // wartosc na lewym koncu
    double& fb              // wartosc na prawym koncu
);

void secant(
    double (*f)(double),    // funkcja kt�rej zera szukamy w [a, b] 
    double& a,              // lewy koniec przedzia�u
    double& b,              // prawy koniec przedzia�u
    double& fa,             // wartosc na lewym koncu
    double& fb              // wartosc na prawym koncu
);

double findZero(
    double (*f)(double),  // funkcja kt�rej zera szukamy w [a, b] 
    double a,             // lewy koniec przedzia�u
    double b,             // prawy koniec przedzia�u
    int M,                // maksymalna dozwolona liczba wywo�a� funkcji f
    double eps,           // spodziewana dok�adno�� zera
    double delta          // wystarczaj�cy b��d bezwzgl�dny wyniku
);