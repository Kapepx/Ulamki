#include <stdlib.h>
#include <stdio.h>
#include "frac.h"

Fraction Fraction :: operator + (double val)
{
    double trueDenom, trueNum;
    GetTrueValues(&trueNum, &trueDenom);

    //printf("TrueNum: %lf\n", trueNum);
    return Fraction(trueNum + (val * trueDenom), trueDenom).GetReduced();
}

Fraction Fraction :: operator - (double val)
{
    double trueDenom, trueNum;
    GetTrueValues(&trueNum, &trueDenom);

    return Fraction(trueNum - (val * trueDenom), trueDenom).GetReduced();
}

Fraction Fraction :: operator * (double val)
{
    double trueDenom, trueNum;
    GetTrueValues(&trueNum, &trueDenom);

    return Fraction(trueNum * val, trueDenom).GetReduced();
}

Fraction Fraction :: operator / (double val)
{
    double trueDenom, trueNum;
    GetTrueValues(&trueNum, &trueDenom);

    return Fraction(trueNum, trueDenom * val).GetReduced();
}

Fraction Fraction :: operator + (Fraction &frac)
{
    double trueDenom1, trueNum1, trueDenom2, trueNum2;
    GetTrueValues(&trueNum1, &trueDenom1);
    frac.GetTrueValues(&trueNum2, &trueDenom2);

    trueNum1 = (trueNum1 * trueDenom2) + (trueNum2 * trueDenom1);
    trueDenom1 = trueDenom1 * trueDenom2;
    return Fraction(trueNum1, trueDenom1).GetReduced();
}

Fraction Fraction :: operator - (Fraction &frac)
{
    double trueDenom1, trueNum1, trueDenom2, trueNum2;
    GetTrueValues(&trueNum1, &trueDenom1);
    frac.GetTrueValues(&trueNum2, &trueDenom2);

    trueNum1 = (trueNum1 * trueDenom2) - (trueNum2 * trueDenom1);
    trueDenom1 = trueDenom1 * trueDenom2;
    return Fraction(trueNum1, trueDenom1).GetReduced();
}

Fraction Fraction :: operator * (Fraction &frac)
{
    double trueDenom1, trueNum1, trueDenom2, trueNum2;
    GetTrueValues(&trueNum1, &trueDenom1);
    frac.GetTrueValues(&trueNum2, &trueDenom2);

    trueNum1 = trueNum1 * trueNum2;
    trueDenom1 = trueDenom1 * trueDenom2;
    return Fraction(trueNum1, trueDenom1).GetReduced();
}

Fraction Fraction :: operator / (Fraction &frac)
{
    double trueDenom1, trueNum1, trueDenom2, trueNum2;
    GetTrueValues(&trueNum1, &trueDenom1);
    frac.GetTrueValues(&trueNum2, &trueDenom2);

    trueNum1 = trueNum1 * trueDenom2;
    trueDenom1 = trueDenom1 * trueNum2;
    return Fraction(trueNum1, trueDenom1).GetReduced();
}

void Fraction::Reduce()
{
    double trueNum, trueDenom;
    GetTrueValues(&trueNum, &trueDenom);
    double nwd = NWD(trueNum, trueDenom);

    if ((trueNum / nwd) == (long long)(trueNum / nwd) && (trueDenom / nwd) == (long long)(trueDenom /nwd))
    {
        SetNum(trueNum / nwd);
        SetDenom(trueDenom / nwd);
    }
}

Fraction Fraction::GetReduced()
{
    double trueNum, trueDenom;
    GetTrueValues(&trueNum, &trueDenom);
    double nwd = NWD(trueNum, trueDenom);

    if ((trueNum / nwd) == (long long)(trueNum / nwd) && (trueDenom / nwd) == (long long)(trueDenom /nwd))
    {
        return Fraction(trueNum / nwd, trueDenom / nwd);
    }
    else
    {
        return Fraction(trueNum, trueDenom);
    }
}
