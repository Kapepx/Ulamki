#ifndef H_FRAC
#define H_FRAC 1
#define FRAC_TYPE_DOUBLE 0
#define FRAC_TYPE_FRAC 1
#define FRAC_PRINT_ERRORS 1
class Fraction
{
public:
    struct
    {
        unsigned char valType : 1;
        unsigned char dynaAlloc : 1;
        union
        {
            double dblVal;
            Fraction *fracVal;
        } val;
    } num, denom;

//public:
    Fraction();
    Fraction(double p_whole);
    Fraction(double p_num, double p_denom);
    Fraction(double p_whole, double p_num, double p_denom);
    ~Fraction();
    void Print();
    void SetNum(double val);
    void SetNum(Fraction &Frac);
    void SetNum(Fraction *Frac);
    void SetDenom(double val);
    void SetDenom(Fraction &Frac);
    void SetDenom(Fraction *Frac);
    long long GetWholes();
    double GetNumAsDbl();
    double GetDenomAsDbl();
    Fraction GetNumAsFrac();
    Fraction GetDenomAsFrac();
    void* GetNumRaw(unsigned char *out_type);
    void* GetDenomRaw(unsigned char *out_type);
    double GetValue();
    void GetTrueValues(double *num, double *denom);
    Fraction operator + (double val);
    Fraction operator - (double val);
    Fraction operator * (double val);
    Fraction operator / (double val);
    Fraction operator + (Fraction &frac);
    Fraction operator - (Fraction &frac);
    Fraction operator * (Fraction &frac);
    Fraction operator / (Fraction &frac);
    void Reduce();
    Fraction GetReduced();
};
double NWD(double a, double b);
#endif // H_FRAC
