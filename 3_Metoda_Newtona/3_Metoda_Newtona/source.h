#pragma once

constexpr double relative_error = 1e-6;
constexpr double absolute_error = 1e-14;

inline double abso(double x) { return x<0 ? -x : x; }
inline double max2(double x, double y) { return x>=y ? x : y; }
inline bool inAbsErr(const double x) { return abso(x)<absolute_error; }

/* Prints vector x of length N. */
void printVector(const double* x, unsigned N);

/*
    @return
    true - if matrix is reversible
*/
bool reverseMatrix2D(double* A);

/*
  Dimensions:
    A - 2x2
    B - 2x1
*/
void multiplyMatrix(const double* A, const double* B, double* C);

/*
*   @param
    x - tablica dlugosci N, okreslajaca wektor, dla ktorego liczona jest wartosc funkcji
    y - tablica dlugosci M, do ktorej funkcja wpisze obliczone f(x). Funkcja zaklada, ze tablica y ma co najmniej M elementow!
    Df - tablica dlugosci M*N, do ktorej funkcja wpisze obliczona macierz rozniczki Df(x). Funkcja zaklada, ze tablica Df ma co najmniej N*M elementow!

    Macierze beda reprezentowane jako jednowymiarowe tablice. Wiersze macierzy beda ukladane w tablicy jeden za drugim.
*/
typedef void (*FuncPointer)(const double* x, double* y, double* Df);

/*
    Funkcja ma obliczyc i wydrukowac na ekran wybrane punkty x1,x2,...,xk spelniajace rownanie:     f(xi)=(f1(xi),f2(xi))=(0,0)
    z dokladnoscia co najmniej max(|fi(xi)|,|f2(xi)|) <= 10e-14.
    
    Przy ustalonej wartosci zmiennej c jest to funkcja fc:R2 ->R2, ktorej miejsca zerowe mozemy wyliczac metoda Newtona.
    Zadaniem jest obliczenie i wydrukowanie na ekran miejsc zerowych fc oraz wartosci parametru c dla c rownych kolejno:
      x[2]+h, x[2]+2*h, ..., x[2]+k*h.

    Argumentami sa:
    f - wskaznik do funkcji R3 -> R2
    x - tablica liczb double dlugosci 3, zawierajaca punkt poczatkowy bliski miejsca zerowego funkcji (czyli f(x)~=(0,0))
    k - okresla liczbe punktow do wyznaczenia
    h - krok zmiany parametru. Funkcje f mozemy traktowac jako:     f(a,b,c) = (f1(a,b,c),f2(a,b,c))

    @return
    jesli dla pewnego i=1,...,k nie uda sie wyznaczyc zera funkcji dla c=x[2]+i*h i z tolerancja absolutna 10e-14 (na przyklad metoda numeryczna bedzie rozbiezna),
    to nalezy zakonczyc dzialanie funkcji bez wypisywania blednego miejsca zerowego i zwrocic indeks i, dla ktorego nastapil problem.
    W przeciwnym przypadku zwracamy wartosc 0 oznaczajaca brak bledu.
*/
int findCurve(FuncPointer f, double* x, unsigned k, double h);

/*
    Funkcja ta ma obliczyc i wydrukowac na ekran wybrane punkty x1,x2,...,xk1*k2 spelniajace rownanie f(xi)=0 z dokladnoscia |f(xi)|<=10e-14.
    
    Argumentami sa:
    f - wskaznik do funkcji R3 -> R
    x - tablica liczb double dlugosci 3, zawierajaca punkt poczatkowy bliski miejsca zerowego funkcji (czyli f(x)~=0)
    k1,k2 - okreslaja liczby punktow do wyznaczenia
    h1,h2 - kroki zmiany parametrow. Przy ustalonej wartosci ostatnich dwoch zmiennych b,c jest to funkcja jednej zmiennej fb,c:R ->R,
       ktorej miejsca zerowe mozemy wyliczyc na przyklad za pomoca metody Newtona.
       Pastwa zadaniem jest obliczenie i wydrukowanie na ekran miejsc zerowych fb,c oraz wartosci b,c dla (b,c) rownych (w podanej kolejnosci):

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
    jesli dla pewnego i=1,...,k1, j=1,...,k2 nie uda sie wyznaczyc zera funkcji dla parametrow b=x[1]+i*h1, c=x[2]+j*h2 z tolerancja absolutna 10e-14,
    to nalezy zakonczyc dzialanie funkcji bez wypisywania blednego miejsca zerowego i zwrocic wartosc i*k1+j.
    W przeciwnym przypadku zwracamy wartosc 0 oznaczajaca brak bledu.
*/
int findSurface(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2);

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
int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2);

