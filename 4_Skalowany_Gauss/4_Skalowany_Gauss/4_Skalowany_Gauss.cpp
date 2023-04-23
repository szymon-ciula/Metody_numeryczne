#include <iostream>
#include "vectalg.h"
#include "source.h"

using namespace std;

int main()
{
    /*Matrix A(4);
    Matrix B {{1., 2.},{1.4, 1.23}};
    A = B;
    Matrix C(A);
    A(0,0) = 5;
    cout << A << endl;
    cout << C << C.size() << endl;
   
    Vector v(3);
    v[0] = -1; v[1] = 9; v[2] = 10;
    Vector w = {1,2,3,5};
    cout << v << endl;
    cout << w << endl;
    cout << v.max_norm() << v.size() << endl;
    // v[3] = 4; // ERROR!
    return 0;*/

    cout.precision(17);
    int n = 2;
    double eps = 0;

    // wczytywanie danych
    // cin >> n;
    Matrix a {{1.,2.},{4.,2.}};
    Vector b {1.,2.};
    //cin >> a >> b >> eps;

    Vector x = solveEquations(a, b, eps);

    auto residual = residual_vector(a, b, x);
    cout << "rozwiazanie = " << x << endl;
    cout << "rezydualny = " << residual << endl;
    cout << "blad = " << residual.max_norm()
         << " limit = " << eps << endl ;
    cout << "Test " << (residual.max_norm() < eps ? "":"nie ") << "zaliczony" << endl; 
    return 0;
}
