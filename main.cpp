#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "frac.h"

using namespace std;

int main()
{
    Fraction F1(234, 45), F2(12, 6), F3;
    F1.Print();
    F2.Print();

    printf("====================\n");
    F3.SetNum(F1);
    F3.SetDenom(F2);
    F3.Print();

    printf("pre: \t");
    F3.GetNumAsFrac().Print();

    F3.NumAdd(4.8);

    printf("post: \t");
    F3.GetNumAsFrac().Print();

    F3.Print();
    printf("====================\n");
    printf("pre simplify:\n\tnumType: %d\n\tdenomType: %d\n\t", F3.GetNumType(), F3.GetDenomType());
    F3.Print();
    F3.Simplify();
    printf("post simplify:\n\tnumType: %d\n\tdenomType: %d\n\t", F3.GetNumType(), F3.GetDenomType());
    F3.Print();
    printf("====================\n");

    F1 = F1 + F2;
    F1.Print();
    return 0;
}
