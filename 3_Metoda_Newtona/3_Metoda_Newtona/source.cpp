// Szymon Ciula

#include <cstdio>
#include "source.h"

using namespace std;

void printVector(const double* x, unsigned N)
{
    for(unsigned i=0;i<N;++i)
        printf("%17.17f ",x[i]);
    printf("\n");
}