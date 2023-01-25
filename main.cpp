#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "frac.h"

using namespace std;

int main()
{
    Fraction F1(1, 3), F2(1, 2), F3;

    F3.SetNum(F1);
    printf("F3.num.dyna: %d\nF3.num.num.dbl: %lf\nF3.num.denom.dbl: %lf\n", F3.num.dynaAlloc, F3.num.val.fracVal->num.val.dblVal, F3.num.val.fracVal->denom.val.dblVal);
    F3.Print();

    F1.Print();
    F2.Print();

    F2 = F2 + 5;
    F2.Print();
    F2 = F2 * 2;
    F2.Print();
    F2 = F2 - 8;
    F2.Print();
    F2 = F2 / 2;
    F2.Print();

    F2 = F2 + F1;
    F2.Print();

    F2 = F2 - F1;
    F2.Print();

    F2 = F2 * F1;
    F2.Print();

    F2 = F2 / F1;
    F2.Print();
    printf("Calosci: %ld\n", F2.GetWholes());
    return 0;
}
