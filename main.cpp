#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "frac.h"

using namespace std;

int main()
{
    Fraction F1(234, 45), F2(12, 6);
    F1.Print();
    F2.Print();
    F1 = F1 + F2;
    F1.Print();
    return 0;
}

long long NWD(long long a, long long b)
{
    while (a != b)
    {
        if (a > b)
            a -= b;
        else
            b -= a;

        if (a <= 1 || b <= 1)
            return 1;
    }

    return a;
}

long long NWW(long long a, long long b)
{
    return (a * b) / NWD(a, b);
}
