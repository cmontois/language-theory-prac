#include "hoc.h"
#include "symbol.h"
#include <math.h>

// Constantes Flottantes
static struct { char *constName; double constValue; } floConsts[] =
{
    "PI",       3.14159265358979323846,
    "E",        2.71828182845904523536,
    "GAMMA",    0.57721566490153286060,
    "DEG",      57.29577951308232087680,
    "PHI",      1.61803398874989484820,
    NULL,       0
};
double Log(double x)    { return errorCheck(log(x), "Erreur de calcul"); }
double Log10(double x)  { return errorCheck(log10(x),"Erreur de calcul"); }
double Exp(double x)    { return errorCheck(exp(x),"Erreur de calcul"); }
double Sqrt(double x)   { return errorCheck(sqrt(x),"Erreur de calcul"); }
// Fonctions prédéfinies sur les flottants
static struct { char *predefName; double (*predefFuncPtr) (); } predefs[] =
 {
     "sin",      sin,
     "cos",      cos,
     "tg",       tan,
     "abs",      fabs,
     "log",      Log,  /* Verifier les arguments */
     "log10",    Log10,  /* Verifier les arguments */
     "exp",      Exp,  /* Verifier les arguments */
     "sqrt",      Sqrt,  /* Verifier les arguments */
     NULL,       0
};

/* Installe les constantes et predefs */
void installDefaultSymbols(void)
{
    int i;
    symbol_ptr_t sp;
    value_t  v;
    
    fprintf(stdout,"Loading: Float Constants ");

    for (i = 0; floConsts[i].constName != NULL;  i++) {
        v.fValue = floConsts[i].constValue;
        sp = installSymbol(floConsts[i].constName, CSTFLO, v);
    }

    fprintf(stdout,"(done)\nLoading: Float Functions ");

    for (i = 0; predefs[i].predefName != NULL; i++) {
        v.func = predefs[i].predefFuncPtr;
        sp = installSymbol(predefs[i].predefName, PREDEF, v);
    }

    fprintf(stdout,"(done).\n");
}







