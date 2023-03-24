// Szymon Ciula

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


struct Triple
{
    float x1, x2, x3;
    Triple(const float x1_, const float x2_, const float x3_) : x1{ x1_ }, x2{ x2_ }, x3{ x3_ } {}
};

inline ostream& operator<< (ostream& out, const Triple& triple)
{
    return (out << triple.x1 << ' ' << triple.x2 << ' ' << triple.x3);
}

inline short sign(const float x)
{
    return x>0  ?  1  :  (x<0 ? -1 : 0);
}

const Triple findTriple(const float product, const float sum);


int main()
{
    int N;
    float x1, x2, x3;
    float sum, product;

    cin >> N;

    for (int i = N; i > 0; --i)
    {
        cin >> product >> sum;
        cout << fixed << setprecision(10) << scientific << findTriple(product, sum) << '\n';
    }

    return 0;
}

const Triple findTriple(const float product, const float sum)
{
    if(product == 0)
        return Triple(0, 0, 0);

    float x1, x2, x3;
    x2 = cbrtf(product); // x1*x2*x3 = x2^3 dla ciagu geometrycznego
// Wyroznik rozbijany na czynniki, aby zmniejszyc podatnosc na przepelnienie i bledy zaokraglen.
    float delta1 = sum + x2;
    float delta2 = sum - 3 * x2;
    float sgn1 = sign(delta1);
    float sgn2 = sign(delta2);

    if (sgn1 * sgn2 == -1)
        return Triple(0, 0, 0);
    else if (sgn1 * sgn2 == 0)
    {
        x1 = (sum - x2)/2;
        x3 = sum - x2 - x1;
        return Triple(x1,x2,x3);
    }
    else
    {
        float delta = sqrtf(sgn1*delta1)*sqrtf(sgn2*delta2); // Pojedyncze czynniki moglyby byc ujemne.

        x1 = (sum-x2 - sign(x2-sum)*delta) / 2; // Przemnozenie delty przez znak wsp. b w celu uniknac odejmowania dwoch bliskich liczb.
        x3 = x2*x2/x1; // Dwa rozwiazania tozsame z naszymi x1 i x3.

        return (x1 < x3)  ?  Triple(x3,x2,x1) : Triple(x1,x2,x3);
    }
}
