#include <stdlib.h>
#include <stdio.h>
#include "frac.h"

Fraction::Fraction()
{
    num.val.dblVal = 1;
    num.valType = FRAC_TYPE_DOUBLE;
    denom.val.dblVal = 1;
    denom.valType = FRAC_TYPE_DOUBLE;
}

Fraction::Fraction(double p_whole)
{
    num.val.dblVal = p_whole;
    num.valType = FRAC_TYPE_DOUBLE;
    denom.val.dblVal = 1;
    denom.valType = FRAC_TYPE_DOUBLE;
}

Fraction::Fraction(double p_num, double p_denom)
{
    if (p_denom != 0)
    {
        denom.val.dblVal = p_denom;
    }
    else
    {
        denom.val.dblVal = 1;
        #ifdef FRAC_PRINT_ERRORS
        printf("Mianownik nie może być równy 0");
        #endif // FRAC_PRINT_ERRORS
    }
    denom.valType = FRAC_TYPE_DOUBLE;

    num.val.dblVal = p_num;
    num.valType = FRAC_TYPE_DOUBLE;
}

Fraction::Fraction(double p_whole, double p_num, double p_denom)
{
    if (p_denom != 0)
    {
        denom.val.dblVal = p_denom;
    }
    else
    {
        denom.val.dblVal = 1;
        #ifdef FRAC_PRINT_ERRORS
        printf("Mianownik nie moze byc rowny 0");
        #endif // FRAC_PRINT_ERRORS
    }
    denom.valType = FRAC_TYPE_DOUBLE;

    num.val.dblVal = p_whole * denom.val.dblVal + p_num;
    num.valType = FRAC_TYPE_DOUBLE;
}

void Fraction::Print()
{
    printf("Fraction: %lf / %lf = %lf\n", GetNumAsDbl(), GetDenomAsDbl(), GetValue());
}

void Fraction::SetNum(double val)
{
    num.valType = FRAC_TYPE_DOUBLE;
    num.val.dblVal = val;
}

void Fraction::SetNum(Fraction &Frac)
{
    num.valType = FRAC_TYPE_FRAC;
    num.val.fracVal = new Fraction();
    num.val.fracVal->SetNum(Frac.GetNumAsDbl());
}

void Fraction::SetDenom(double val)
{
    if (val == 0)
    {
        #ifdef FRAC_PRINT_ERRORS
        printf("Mianownik nie moze byc rowny 0");
        #endif // FRAC_PRINT_ERRORS
        return;
    }

    denom.valType = FRAC_TYPE_DOUBLE;
    denom.val.dblVal = val;
}

double Fraction::GetNumAsDbl()
{
    if (num.valType == FRAC_TYPE_DOUBLE)
    {
        return num.val.dblVal;
    }
    else
    {
        if (num.val.fracVal == 0)
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Licznik wskazuje na nie istniejacy ulamek");
            #endif // FRAC_PRINT_ERRORS
            return 0;
        }
        else
        {
            return num.val.fracVal->GetValue();
        }
    }
}

double Fraction::GetDenomAsDbl()
{
    if (denom.valType == FRAC_TYPE_DOUBLE)
    {
        return denom.val.dblVal;
    }
    else
    {
        if (denom.val.fracVal == 0)
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Licznik wskazuje na nie istniejacy ulamek");
            #endif // FRAC_PRINT_ERRORS
            return 0;
        }
        else
        {
            return denom.val.fracVal->GetValue();
        }
    }
}

//TODO
Fraction Fraction::GetNumAsFrac()
{
    if (num.valType == FRAC_TYPE_DOUBLE)
    {
        return Fraction(num.val.dblVal);
    }
    else
    {
        return *num.val.fracVal;
    }
}

//TODO
Fraction Fraction::GetDenomAsFrac()
{
    if (denom.valType == FRAC_TYPE_DOUBLE)
    {
        return Fraction(denom.val.dblVal);
    }
    else
    {
        return *denom.val.fracVal;
    }
}

void* Fraction::GetNumRaw(unsigned char *out_type)
{
    if (out_type == 0)
    {
        #ifdef FRAC_PRINT_ERRORS
        printf("Nie przekazano zmiennej na przechowanie typu\n");
        #endif
    }

    *out_type = num.valType;
    return &num.val;
}

void* Fraction::GetDenomRaw(unsigned char *out_type)
{
    if (out_type == 0)
    {
        #ifdef FRAC_PRINT_ERRORS
        printf("Nie przekazano zmiennej na przechowanie typu\n");
        #endif // FRAC_PRINT_ERRORS
    }

    *out_type = num.valType;
    return &num.val;
}

double Fraction::GetValue()
{
    double result = 0;
    if (num.valType == FRAC_TYPE_DOUBLE)
    {
        result += num.val.dblVal;
    }
    else
    {
        if (num.val.fracVal == 0)
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Licznik wskazuje na nie istniejacy ulamek");
            printf("Typ licznika = %i\n", num.valType);
            #endif // FRAC_PRINT_ERRORS
        }
        else
        {
            result += num.val.fracVal->GetValue();
        }
    }

    if (denom.valType == FRAC_TYPE_DOUBLE)
    {
        return result / denom.val.dblVal;
    }
    else
    {
        if (denom.val.fracVal == 0)
        {
            #ifdef FRAC_PRINT_ERRORS
            printf("Mianownik wskazuje na nie istniejacy ulamek");
            #endif // FRAC_PRINT_ERRORS
            return result;
        }
        else
        {
            return result / denom.val.fracVal->GetValue();
        }
    }
}

void Fraction::GetTrueValues(double *p_num, double *p_denom)
{
    if (denom.valType == FRAC_TYPE_FRAC)
    {
        *p_denom = denom.val.fracVal->GetDenomAsDbl();
    }
    else
    {
        *p_denom = denom.val.dblVal;
    }
    if (*p_denom == 0)
    {
        printf("Jest zle\n");
        *p_num = 0;
        *p_denom = 0;
        return;
    }

    if  (num.valType == FRAC_TYPE_FRAC)
    {
        *p_num = num.val.fracVal->GetNumAsDbl();
    }
    else
    {
        *p_num = num.val.dblVal;
    }
}
