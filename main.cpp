#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#define FRAC_PRINT_ERRORS 1

#define FRAC_TYPE_DOUBLE 0
#define FRAC_TYPE_FRAC 1

using namespace std;

class Fraction
{
    struct
    {
        unsigned char valType : 1;
        union
        {
            double dblVal;
            Fraction *fracVal;
        } val;
    } num, denom;

public:
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
            printf("Mianownik nie mo¿e byæ równy 0");
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

};

int main()
{
    Fraction F1, F2(1, 2);
    printf("F1: %Lf\n", F1.GetValue());
    printf("F2: %Lf\n", F2.GetValue());
    return 0;
}
