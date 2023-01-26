#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "frac.h"

using namespace std;

int main()
{
    Fraction F1(6, 2);
    F1.Print();
    F1.Reduce();
    F1.Print();

    F1 = F1 + 5;
    F1.Print();

    F1 = F1 - 3;
    F1.Print();

    F1 = F1 * 2;
    F1.Print();

    F1 = F1 / 3;
    F1.Print();
    return 0;
}

double NWD(double a, double b)
{
    while (a != b && a > 1 && b > 1)
    {
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}
