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

    if ((long long)trueDenom1 == trueDenom1 && (long long)trueDenom2 == trueDenom2)
    {
        long long nww = NWW(trueDenom1, trueDenom2);
        trueNum1 = trueNum1 * (nww / trueDenom1);
        trueNum2 = trueNum2 * (nww / trueDenom2);
        trueNum1 += trueNum2;
        trueDenom1 = nww;
    }
    else
    {
        trueNum1 = (trueNum1 * trueDenom2) + (trueNum2 * trueDenom1);
        trueDenom1 = trueDenom1 * trueDenom2;
    }

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

void Fraction::NumAdd(double val)
{
    if (num.valType == FRAC_TYPE_DOUBLE)
    {
        num.val.dblVal += val;
    }
    else
    {
        if (num.val.fracVal != 0)
        {
            *num.val.fracVal = *num.val.fracVal + val;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba dodania do nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::NumAdd(Fraction &Frac)
{
    if (num.valType == FRAC_TYPE_DOUBLE)
    {
        num.val.dblVal += Frac.GetValue();
    }
    else
    {
        if (num.val.fracVal != 0)
        {
            *num.val.fracVal = *num.val.fracVal + Frac;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba dodania do nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::NumSub(double val)
{
    if (num.valType == FRAC_TYPE_DOUBLE)
    {
        num.val.dblVal -= val;
    }
    else
    {
        if (num.val.fracVal != 0)
        {
            *num.val.fracVal = *num.val.fracVal - val;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba odjêcia od nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::NumSub(Fraction &Frac)
{
    if (num.valType == FRAC_TYPE_DOUBLE)
    {
        num.val.dblVal -= Frac.GetValue();
    }
    else
    {
        if (num.val.fracVal != 0)
        {
            *num.val.fracVal = *num.val.fracVal - Frac;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba odjêcia od nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::NumMult(double val)
{
    if (num.valType == FRAC_TYPE_DOUBLE)
    {
        num.val.dblVal *= val;
    }
    else
    {
        if (num.val.fracVal != 0)
        {
            *num.val.fracVal = *num.val.fracVal * val;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba mno¿enia nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::NumMult(Fraction &Frac)
{
    if (num.valType == FRAC_TYPE_DOUBLE)
    {
        num.val.dblVal *= Frac.GetValue();
    }
    else
    {
        if (num.val.fracVal != 0)
        {
            *num.val.fracVal = *num.val.fracVal * Frac;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba mno¿enia nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::NumDiv(double val)
{
    if (num.valType == FRAC_TYPE_DOUBLE)
    {
        num.val.dblVal /= val;
    }
    else
    {
        if (num.val.fracVal != 0)
        {
            *num.val.fracVal = *num.val.fracVal / val;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba dzielenia nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::NumDiv(Fraction &Frac)
{
    if (num.valType == FRAC_TYPE_DOUBLE)
    {
        num.val.dblVal /= Frac.GetValue();
    }
    else
    {
        if (num.val.fracVal != 0)
        {
            *num.val.fracVal = *num.val.fracVal / Frac;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba dzielenia nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::DenomAdd(double val)
{
    if (denom.valType == FRAC_TYPE_DOUBLE)
    {
        denom.val.dblVal += val;
    }
    else
    {
        if (denom.val.fracVal != 0)
        {
            *denom.val.fracVal = *denom.val.fracVal + val;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba dodania do nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::DenomAdd(Fraction &Frac)
{
    if (denom.valType == FRAC_TYPE_DOUBLE)
    {
        denom.val.dblVal += Frac.GetValue();
    }
    else
    {
        if (denom.val.fracVal != 0)
        {
            *denom.val.fracVal = *denom.val.fracVal + Frac;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba dodania do nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::DenomSub(double val)
{
    if (denom.valType == FRAC_TYPE_DOUBLE)
    {
        denom.val.dblVal -= val;
    }
    else
    {
        if (denom.val.fracVal != 0)
        {
            *denom.val.fracVal = *denom.val.fracVal - val;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba odjêcia od nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::DenomSub(Fraction &Frac)
{
    if (denom.valType == FRAC_TYPE_DOUBLE)
    {
        denom.val.dblVal -= Frac.GetValue();
    }
    else
    {
        if (denom.val.fracVal != 0)
        {
            *denom.val.fracVal = *denom.val.fracVal - Frac;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba odjêcia od nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::DenomMult(double val)
{
    if (denom.valType == FRAC_TYPE_DOUBLE)
    {
        denom.val.dblVal *= val;
    }
    else
    {
        if (denom.val.fracVal != 0)
        {
            *denom.val.fracVal = *denom.val.fracVal * val;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba mno¿enia nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::DenomMult(Fraction &Frac)
{
    if (denom.valType == FRAC_TYPE_DOUBLE)
    {
        denom.val.dblVal *= Frac.GetValue();
    }
    else
    {
        if (denom.val.fracVal != 0)
        {
            *denom.val.fracVal = *denom.val.fracVal * Frac;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba mno¿enia nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::DenomDiv(double val)
{
    if (denom.valType == FRAC_TYPE_DOUBLE)
    {
        denom.val.dblVal /= val;
    }
    else
    {
        if (denom.val.fracVal != 0)
        {
            *denom.val.fracVal = *denom.val.fracVal / val;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba dzielenia nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}

void Fraction::DenomDiv(Fraction &Frac)
{
    if (denom.valType == FRAC_TYPE_DOUBLE)
    {
        denom.val.dblVal /= Frac.GetValue();
    }
    else
    {
        if (denom.val.fracVal != 0)
        {
            *denom.val.fracVal = *denom.val.fracVal / Frac;
        }
        else
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Próba dzielenia nieistniej¹cego u³amka\n");
            #endif // FRAC_PRINT_ERRORS
        }
    }
}
