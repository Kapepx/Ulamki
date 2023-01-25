#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "frac.h"
#define FRAC_PRINT_ERRORS 1

using namespace std;

int main()
{
    Fraction F1(1, 3), F2(1, 2);

    F1.Print();

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
    return 0;
}
