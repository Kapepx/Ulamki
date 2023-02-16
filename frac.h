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
    void NumAdd(double val);
    void NumAdd(Fraction &Frac);
    void NumSub(double val);
    void NumSub(Fraction &Frac);
    void NumMult(double val);
    void NumMult(Fraction &Frac);
    void NumDiv(double val);
    void NumDiv(Fraction &Frac);

    void SetDenom(double val);
    void SetDenom(Fraction &Frac);
    void SetDenom(Fraction *Frac);
    void DenomAdd(double val);
    void DenomAdd(Fraction &Frac);
    void DenomSub(double val);
    void DenomSub(Fraction &Frac);
    void DenomMult(double val);
    void DenomMult(Fraction &Frac);
    void DenomDiv(double val);
    void DenomDiv(Fraction &Frac);

    long long GetWholes();
    double GetNumAsDbl();
    double GetDenomAsDbl();
    Fraction GetNumAsFrac();
    Fraction GetDenomAsFrac();
    void* GetNumRaw(unsigned char *out_type);
    void* GetDenomRaw(unsigned char *out_type);
    unsigned char GetNumType();
    unsigned char GetDenomType();
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
    void Simplify();
    void Reduce();
    void Reduce(double val);
    void Extend(double val);
    Fraction GetReduced();
};
long long NWD(long long a, long long b);
long long NWW(long long a, long long b);
#endif // H_FRAC
