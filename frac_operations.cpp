#include <stdlib.h>
#include <stdio.h>
#include "frac.h"

Fraction Fraction :: operator + (double val)
{
    double trueDenom, trueNum;
    GetTrueValues(&trueNum, &trueDenom);

    return Fraction(trueNum + (val * trueDenom), trueDenom);
}

Fraction Fraction :: operator - (double val)
{
    double trueDenom, trueNum;
    GetTrueValues(&trueNum, &trueDenom);

    return Fraction(trueNum - (val * trueDenom), trueDenom);
}

Fraction Fraction :: operator * (double val)
{
    double trueDenom, trueNum;
    GetTrueValues(&trueNum, &trueDenom);

    return Fraction(trueNum * val, trueDenom);
}

Fraction Fraction :: operator / (double val)
{
    double trueDenom, trueNum;
    GetTrueValues(&trueNum, &trueDenom);

    return Fraction(trueNum, trueDenom * val);
}

Fraction Fraction :: operator + (Fraction &frac)
{
    double trueDenom1, trueNum1, trueDenom2, trueNum2;
    GetTrueValues(&trueNum1, &trueDenom1);
    frac.GetTrueValues(&trueNum2, &trueDenom2);

    trueNum1 = (trueNum1 * trueDenom2) + (trueNum2 * trueDenom1);
    trueDenom1 = trueDenom1 * trueDenom2;
    return Fraction(trueNum1, trueDenom1);
}

Fraction Fraction :: operator - (Fraction &frac)
{
    double trueDenom1, trueNum1, trueDenom2, trueNum2;
    GetTrueValues(&trueNum1, &trueDenom1);
    frac.GetTrueValues(&trueNum2, &trueDenom2);

    trueNum1 = (trueNum1 * trueDenom2) - (trueNum2 * trueDenom1);
    trueDenom1 = trueDenom1 * trueDenom2;
    return Fraction(trueNum1, trueDenom1);
}

Fraction Fraction :: operator * (Fraction &frac)
{
    double trueDenom1, trueNum1, trueDenom2, trueNum2;
    GetTrueValues(&trueNum1, &trueDenom1);
    frac.GetTrueValues(&trueNum2, &trueDenom2);

    trueNum1 = trueNum1 * trueNum2;
    trueDenom1 = trueDenom1 * trueDenom2;
    return Fraction(trueNum1, trueDenom1);
}

Fraction Fraction :: operator / (Fraction &frac)
{
    double trueDenom1, trueNum1, trueDenom2, trueNum2;
    GetTrueValues(&trueNum1, &trueDenom1);
    frac.GetTrueValues(&trueNum2, &trueDenom2);

    trueNum1 = trueNum1 * trueDenom2;
    trueDenom1 = trueDenom1 * trueNum2;
    return Fraction(trueNum1, trueDenom1);
}
