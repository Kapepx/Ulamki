#include <stdlib.h>
#include <stdio.h>
#include "frac.h"
#define FRAC_PRINT_ERRORS 1

Fraction::Fraction()
{
    num.val.dblVal = 1;
    num.valType = FRAC_TYPE_DOUBLE;
    num.dynaAlloc = 0;
    denom.val.dblVal = 1;
    denom.valType = FRAC_TYPE_DOUBLE;
    denom.dynaAlloc = 0;
}

Fraction::Fraction(double p_whole)
{
    num.val.dblVal = p_whole;
    num.valType = FRAC_TYPE_DOUBLE;
    num.dynaAlloc = 0;
    denom.val.dblVal = 1;
    denom.valType = FRAC_TYPE_DOUBLE;
    denom.dynaAlloc = 0;
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
    denom.dynaAlloc = 0;
    denom.valType = FRAC_TYPE_DOUBLE;

    num.val.dblVal = p_num;
    num.dynaAlloc = 0;
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

Fraction::~Fraction()
{
    if (num.valType == FRAC_TYPE_FRAC && num.dynaAlloc && denom.val.fracVal != 0)
    {
        delete num.val.fracVal;
    }

    if (denom.valType == FRAC_TYPE_FRAC && denom.dynaAlloc && denom.val.fracVal != 0)
    {
        delete denom.val.fracVal;
    }
}

void Fraction::Print()
{
    printf("Fraction: %lf / %lf = %lf\n", GetNumAsDbl(), GetDenomAsDbl(), GetValue());
}

void Fraction::SetNum(double val)
{
    if (num.valType == FRAC_TYPE_FRAC && num.dynaAlloc)
    {
        delete num.val.fracVal;
    }

    num.valType = FRAC_TYPE_DOUBLE;
    num.dynaAlloc = 0;
    num.val.dblVal = val;
}

void Fraction::SetNum(Fraction &Frac)
{
    if (num.valType == FRAC_TYPE_FRAC && num.dynaAlloc)
    {
        delete num.val.fracVal;
    }

    num.valType = FRAC_TYPE_FRAC;
    num.dynaAlloc = 1;
    num.val.fracVal = new Fraction();

    //Licznik
    unsigned char tempType;
    void *tempVal = Frac.GetNumRaw(&tempType);
    if (tempType == FRAC_TYPE_DOUBLE)
    {
        //Rzutowanie okropne, ale nie zwraca błędu
        num.val.fracVal->SetNum(*(double*)tempVal);
    }
    else
    {
        if (tempVal == 0)
        {
            SetNum(1);
            SetDenom(1);
            return;
        }

        num.val.fracVal->SetNum(*(Fraction*)tempVal);
    }

    //Mianownik
    tempVal = Frac.GetDenomRaw(&tempType);
    if (tempType == FRAC_TYPE_DOUBLE)
    {
        //Rzutowanie okropne, ale nie zwraca błędu
        num.val.fracVal->SetDenom(*(double*)tempVal);
    }
    else
    {
        if (tempVal == 0)
        {
            SetNum(1);
            SetDenom(1);
            return;
        }

        num.val.fracVal->SetDenom(*(Fraction*)tempVal);
    }
}

void Fraction::SetNum(Fraction *Frac)
{
    if (Frac == 0)
    {
        #ifdef FRAC_PRINT_ERRORS
        printf("Przekazano nie istniejacy ulamek\n");
        #endif // FRAC_PRINT_ERRORS
        return;
    }

    if (num.valType == FRAC_TYPE_FRAC && num.dynaAlloc)
    {
        delete num.val.fracVal;
    }

    num.valType = FRAC_TYPE_FRAC;
    num.dynaAlloc = 0;
    num.val.fracVal = Frac;
}

void Fraction::SetDenom(double val)
{
    if (denom.valType == FRAC_TYPE_FRAC && denom.dynaAlloc)
    {
        delete denom.val.fracVal;
    }

    if (val == 0)
    {
        #ifdef FRAC_PRINT_ERRORS
        printf("Mianownik nie moze byc rowny 0");
        #endif // FRAC_PRINT_ERRORS
        return;
    }

    denom.dynaAlloc = 0;
    denom.valType = FRAC_TYPE_DOUBLE;
    denom.val.dblVal = val;
}

void Fraction::SetDenom(Fraction &Frac)
{
    if (denom.valType == FRAC_TYPE_FRAC && denom.dynaAlloc)
    {
        delete denom.val.fracVal;
    }

    denom.valType = FRAC_TYPE_FRAC;
    denom.dynaAlloc = 1;
    denom.val.fracVal = new Fraction();

    //Licznik
    unsigned char tempType;
    void *tempVal = Frac.GetNumRaw(&tempType);
    if (tempType == FRAC_TYPE_DOUBLE)
    {
        //Rzutowanie okropne, ale nie zwraca błędu
        denom.val.fracVal->SetNum(*(double*)tempVal);
    }
    else
    {
        if (tempVal == 0)
        {
            SetNum(1);
            SetDenom(1);
            return;
        }

        denom.val.fracVal->SetNum(*(Fraction*)tempVal);
    }

    //Mianownik
    tempVal = Frac.GetDenomRaw(&tempType);
    if (tempType == FRAC_TYPE_DOUBLE)
    {
        denom.val.fracVal->SetDenom(*(double*)tempVal);
    }
    else
    {
        if (tempVal == 0)
        {
            SetNum(1);
            SetDenom(1);
            return;
        }

        denom.val.fracVal->SetDenom(*(Fraction*)tempVal);
    }
}

void Fraction::SetDenom(Fraction *Frac)
{
    if (Frac == 0)
    {
        #ifdef FRAC_PRINT_ERRORS
        printf("Przekazano nie istniejacy ulamek\n");
        #endif // FRAC_PRINT_ERRORS
        return;
    }

    if (denom.valType == FRAC_TYPE_FRAC && denom.dynaAlloc)
    {
        delete denom.val.fracVal;
    }

    denom.valType = FRAC_TYPE_FRAC;
    denom.dynaAlloc = 0;
    denom.val.fracVal = Frac;
}

long long Fraction::GetWholes()
{
    return (long long)(GetValue());
}

double Fraction::GetNumAsDbl() const
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

double Fraction::GetDenomAsDbl() const
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

Fraction Fraction::GetNumAsFrac() const
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

Fraction Fraction::GetDenomAsFrac() const
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

    *out_type = denom.valType;
    return &denom.val;
}

unsigned char Fraction::GetNumType()
{
    return num.valType;
}

unsigned char Fraction::GetDenomType()
{
    return denom.valType;
}

double Fraction::GetValue() const
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

void Fraction::GetTrueValues(double *p_num, double *p_denom) const
{
    if (denom.valType == FRAC_TYPE_FRAC)
    {
        *p_denom = denom.val.fracVal->GetValue();
    }
    else
    {
        *p_denom = denom.val.dblVal;
    }

    if (*p_denom == 0)
    {
        *p_num = 0;
        *p_denom = 0;
        return;
    }

    if  (num.valType == FRAC_TYPE_FRAC)
    {
        *p_num = num.val.fracVal->GetValue();
    }
    else
    {
        *p_num = num.val.dblVal;
    }
}

void Fraction::Simplify()
{
    double temp;
    if (num.valType == FRAC_TYPE_FRAC && num.val.fracVal != 0)
    {
        temp = num.val.fracVal->GetValue();

        if (num.dynaAlloc)
        {
            delete num.val.fracVal;
        }

        num.val.dblVal = temp;
        num.dynaAlloc = 0;
        num.valType = FRAC_TYPE_DOUBLE;
    }

    if (denom.valType == FRAC_TYPE_FRAC && denom.val.fracVal != 0)
    {
        temp = denom.val.fracVal->GetValue();

        if (denom.dynaAlloc)
        {
            delete denom.val.fracVal;
        }

        denom.val.dblVal = temp;
        denom.dynaAlloc = 0;
        denom.valType = FRAC_TYPE_DOUBLE;
    }
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

void Fraction::Reduce(double val)
{
    double trueNum, trueDenom;
    GetTrueValues(&trueNum, &trueDenom);

    SetNum(trueNum / val);
    SetDenom(trueNum / val);
}

void Fraction::Extend(double val)
{
    double trueNum, trueDenom;
    GetTrueValues(&trueNum, &trueDenom);

    SetNum(trueNum * val);
    SetDenom(trueNum * val);
}

Fraction Fraction::GetReduced()
{
    double trueNum, trueDenom;
    GetTrueValues(&trueNum, &trueDenom);

    if ((long long)trueNum != trueNum || (long long)trueDenom != trueDenom)
    {
        return *this;
    }
    long long nwd = NWD(trueNum, trueDenom);

    if ((trueNum / nwd) == (long long)(trueNum / nwd) && (trueDenom / nwd) == (long long)(trueDenom /nwd))
    {
        return Fraction(trueNum / nwd, trueDenom / nwd);
    }
    else
    {
        return Fraction(trueNum, trueDenom);
    }
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
