//Szymon Ciula

inline short sgn(double x) { return x<0 ? -1 : 1; }

double findZero(
    double (*f)(double),  // funkcja której zera szukamy w [a, b] 
    double a,             // lewy koniec przedzia³u
    double b,             // prawy koniec przedzia³u
    int M,                // maksymalna dozwolona liczba wywo³añ funkcji f
    double eps,           // spodziewana dok³adnoœæ zera
    double delta          // wystarczaj¹cy b³¹d bezwzglêdny wyniku
)
{
    return 0.0;
}

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

)