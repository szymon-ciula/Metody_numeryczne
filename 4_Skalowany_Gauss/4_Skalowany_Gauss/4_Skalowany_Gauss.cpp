#include <iostream>
#include "vectalg.h"
#include "source.h"

using namespace std;

int main()
{
    cout.precision(17);
    int n;
    double eps;

    cin >> n;
    
    Matrix a(n);
    Vector b(n);

    cin >> a >> b >> eps;

    Vector x = solveEquations(a, b, eps);

    auto residual = residual_vector(a, b, x);
    cout << "rozwiazanie = " << x << endl;
    cout << "rezydualny = " << residual << endl;
    cout << "blad = " << residual.max_norm()
         << " limit = " << eps << endl ;
    cout << "Test " << (residual.max_norm() < eps ? "":"nie ") << "zaliczony" << endl;

    return 0;
}
