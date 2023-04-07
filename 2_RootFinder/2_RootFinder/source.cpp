//Szymon Ciula

#include "source.h"


double bisection(
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
        a = (a + b) / 2;
        fa = mid_value;
    }
    else
    {
        b = (a + b) / 2;
        fb = mid_value;
    }

    return mid_value;
}

double Newton(
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

    return fb;
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
    double fa = f(a);
    if(inDelta(fa, delta))
        return a;
    double fb = f(b);
    if(inDelta(fb, delta))
        return b;
    double temp;
    
    while (sgn(fa) * sgn(fb) > 0)
    {
        Newton(f,a,b,fa,fb);
        if(inEps(a,b,eps) || inDelta(fb,delta))
            return b;
    }

    while (!(inEps(a,b,eps) || inDelta(fb,delta)))
    {
        if(inDelta(fa,delta))
            return a;
        temp = b - (fb*(b-a))/(fb-fa);
        if (!inInterval(temp, a, b))
        {
            a = b;
            fa = fb;
            b = temp;
            fb = f(temp);
        }
        else
            bisection(f,a,b,fa,fb);
    }

    return b;
}