#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#define FRAC_PRINT_ERRORS 1

#define FRAC_TYPE_DOUBLE 0
#define FRAC_TYPE_FRAC 1

using namespace std;

class Fraction
{
public:
    struct
    {
        unsigned char valType : 1;
        union
        {
            double dblVal;
            Fraction *fracVal;
        } val;
    } num, denom;


    Fraction()
    {
        num.val.dblVal = 1;
        num.valType = FRAC_TYPE_DOUBLE;
        denom.val.dblVal = 1;
        denom.valType = FRAC_TYPE_DOUBLE;
    }

    Fraction(double p_whole)
    {
        num.val.dblVal = p_whole;
        num.valType = FRAC_TYPE_DOUBLE;
        denom.val.dblVal = 1;
        denom.valType = FRAC_TYPE_DOUBLE;
    }

    Fraction(double p_num, double p_denom)
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

    Fraction(double p_whole, double p_num, double p_denom)
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

    void Print()
    {
        printf("Fraction: %lf / %lf = %lf\n", GetNumAsDbl(), GetDenomAsDbl(), GetValue());
    }

    void SetNum(double val)
    {
        num.valType = FRAC_TYPE_DOUBLE;
        num.val.dblVal = val;
    }

    void SetNum(Fraction &Frac)
    {
        num.valType = FRAC_TYPE_FRAC;
        num.val.fracVal = new Fraction();
        num.val.fracVal->SetNum(Frac.GetNumAsDbl());
    }

    void SetDenom(double val)
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

    double GetNumAsDbl()
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

    double GetDenomAsDbl()
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
    Fraction GetNumAsFrac()
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
    Fraction GetDenomAsFrac()
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

    void* GetNumRaw(unsigned char *out_type)
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

    void* GetDenomRaw(unsigned char *out_type)
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

    double GetValue()
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

    Fraction operator + (double val)
    {
        double trueDenom, trueNum;
        if (denom.valType == FRAC_TYPE_FRAC)
        {
            trueDenom = denom.val.fracVal->GetDenomAsDbl();
        }
        else
        {
            trueDenom = denom.val.dblVal;
        }
        if (trueDenom == 0)
        {
            printf("Jest zle\n");
            return Fraction();
        }

        if  (num.valType == FRAC_TYPE_FRAC)
        {
            trueNum = num.val.fracVal->GetNumAsDbl();
        }
        else
        {
            trueNum = num.val.dblVal;
        }

        return Fraction(trueNum + (val * trueDenom), trueDenom);
    }
};

int main()
{
    Fraction F1, F2(1, 2);

    F1.Print();
    F1.Print();

    F2 = F2 + 5;
    F2.Print();
    return 0;
}
