#include "hoc.h"
#include <math.h>

static struct {char *constName;double constValue;} floConsts[] = {
  "PI",       3.14159265358979323846,
  "E",        2.71828182845904523536,
  "GAMMA",    0.57721566490153286060,
  "DEG",      57.29577951308232087680,
  "PHI",      1.61803398874989484820,
  NULL,       0
};

double Log(double x) {errorCheck(log(x), "Erreur de calcul");}
double Exp(double x) {errorCheck(exp(x), "Erreur de calcul");}
double Sqrt(double x) {errorCheck(sqrt(x), "Erreur de calcul");}

static struct {char *predefName;double (*predefFuncPtr)();} predefs[] = {
  "sin",      sin,
  "cos",      cos,
  "tg",       tan,
  "log",      Log,  /* TODO check parameters*/
  // "log10",    Log10,/* TODO check parameters*/
  "exp",      Exp,  /* TODO check parameters*/
  // "pow",      Pow,  /* TODO check parameters*/
  "sqrt",     Sqrt, /* TODO check parameters*/
  "abs",      fabs,
  NULL,       0
};

void installDefaultSymbols(void) {
  int i;
  value_t v;
  symbol_ptr_t sp;


  fprintf(stdout, "Loading: Float Constants\n");

  for (i = 0; floConsts[i].constName != NULL; i++) {
    v.fValue = floConsts[i].constValue;
    sp = install(floConsts[i].constName, VARFLO, v);
  };


  fprintf(stdout, "Loading: Float Functions\n");

  for (i = 0; predefs[i].predefName != NULL; i++) {
    v.func = predefs[i].predefFuncPtr;
    sp = install(predefs[i].predefName, PREDEF, v);
  }

  fprintf(stdout, "Done");
}