//Szymon Ciula

#include "source.h"

void swap(double& a, double& b)
{
    double temp = a;
    a = b;
    b = temp;
}

void bisection(
    double (*f)(double),    // funkcja której zera szukamy w [a, b] 
    double& a,              // lewy koniec przedzia³u
    double& b,              // prawy koniec przedzia³u
    double& fa,             // wartosc na lewym koncu
    double& fb              // wartosc na prawym koncu
)
{
    double mid_value = f((a+b)/2);

    if (sgn(mid_value) == sgn(fa))
    {
        fa = mid_value;
        a = (a + b) / 2;
    }
    else
    {
        fb = mid_value;
        b = (a + b) / 2;
    }
}

void secant(
    double (*f)(double),    // funkcja której zera szukamy w [a, b] 
    double& a,              // lewy koniec przedzia³u
    double& b,              // prawy koniec przedzia³u
    double& fa,             // wartosc na lewym koncu
    double& fb              // wartosc na prawym koncu
)
{
    double x = b;
    double fx = fb;
    b = b - (fb*(b-a))/(fb-fa);
    fb = f(b);
    a = x;
    fa = fx;
}

double findZero(
    double (*f)(double),  // funkcja której zera szukamy w [a, b] 
    double a,             // lewy koniec przedzia³u
    double b,             // prawy koniec przedzia³u
    int M,                // maksymalna dozwolona liczba wywo³añ funkcji f
    double eps,           // spodziewana dok³adnoœæ zera
    double delta          // wystarczaj¹cy b³¹d bezwzglêdny wyniku
)
{
    // Sprawdzenie czy kraniec nie jest miejscem zerowym.
    double fa = f(a);
    if(inEps(fa, eps))
        return a;
    double fb = f(b);
    if(inEps(fb, eps))
        return b;
    // Wywolujemy metode siecznych dopoki nie bedziemy mogli wywolac metody bisekcji.
    while (sgn(fa) * sgn(fb) > 0)
    {
        secant(f,a,b,fa,fb);
        if(inDelta(a,b,delta) || inEps(fb,eps))
            return b;
    }
    constexpr double edge = 0.0625;
    // Wywolujemy metode bisekcji dopoki wielkosc kroku nie bedzie mniejsza niz pewna stala.
    while( abso(b-a) > edge )
        bisection(f,a,b,fa,fb);

    // Wywolujemy metode siecznych az do uzyskania odpowiedniej dokladnosci.
    while (!(inEps(fb, eps) || inDelta(a, b, delta)))
    {
        if(inEps(fa,eps))
            return a;
        secant(f,a,b,fa,fb);
    }

    return b;
}