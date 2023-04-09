//Szymon Ciula

inline double abso(double x) { return (x<0 ? -x : x); }
inline short sgn(double x) { return x<0 ? -1 : 1; }
inline bool inEps(double a, double b, double eps) { return abso(b-a) < eps; }
inline bool inDelta(double fx, double delta) { return abso(fx)<=delta; }
inline bool inInterval(double x, double a, double b) { return (a<b) ? (a<x && x<b) : (b<x && x<a); }

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
        a = (a + b) / 2;
        fa = mid_value;
    }
    else
    {
        b = (a + b) / 2;
        fb = mid_value;
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
    //b = (fb * a - fa * b) / (fb - fa);
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
    double fa = f(a);
    if(inDelta(fa, delta))
        return a;
    double fb = f(b);
    if(inDelta(fb, delta))
        return b;
    double x, fx, fprev = fa, mid, temp, ftemp;
    int count = 2;
    
    while (sgn(fa) * sgn(fb) > 0)
    {
        secant(f,a,b,fa,fb);
        count++;
        if(inEps(a,b,eps) || inDelta(fb,delta))
            return count;//b;
    }

    while (!(inEps(a,b,eps) || inDelta(fb,delta)))
    {
        mid = (b + a) / 2;
        if (fb != fprev)
            x = b - (fb * (b - a)) / (fb - fa);
        else
            x = mid;
        if (inInterval(x, mid, b))
        {
            temp = b;
            ftemp = fb;
            b = x;
            fb = f(b);
        }
        else
        {
            temp = b;
            ftemp = fb;
            b = mid;
            fb = f(b);
        }
        if (sgn(fa) * sgn(fb) >= 0)
        {
            a = temp;
            fa = ftemp;
        }
        if (abso(fa) < abso(fb))
        {
            swap(a, b);
            swap(fa, fb);
        }
        count++;
    }

    /*do
    {
        count++;
        x = b - (fb*(b-a))/(fb-fa);
        if (inInterval(x, b, (a + b) / 2))
        {
            a = b;
            fa = fb;
            b = x;
            fb = f(x);
        }
        else
        {
            bisection(f, a, b, fa, fb);
            if(inDelta(fa,delta))
                return count;//a;
        }
    } while(!(inEps(a,b,eps) || inDelta(fb,delta)));*/

    //while (/*abso(a - b) > (1 >> 5) && */count <= M)
    /* {
        bisection(f,a,b,fa,fb);
        count++;
        
        if(inDelta(fb, delta))
            return count;//b;
        else if(inDelta(fa, delta))
            return count;//a;
        else if(inEps(a,b,eps))
            return count;//(a+b)/2;
    }

    while (!(inEps(a,b,eps) || inDelta(fb,delta)))
    {
        x = b - (fb*(b-a))/(fb-fa);
        count++;
        if (!inInterval(x, a, b))
        {
            a = b;
            fa = fb;
            b = x;
            fb = f(x);
        }
        else
        {
            bisection(f, a, b, fa, fb);
            if(inDelta(fa,delta))
                return count;//a;
        }
    }*/

    return b;
}