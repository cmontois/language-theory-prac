#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libgen.h>

/**
* Data Structure Symbol
*/

typedef union {         // Depending on the symbol type
  int     iValue;       // - a value if type is VARINT
  double  fValue;       // - a value if type is VARFLO
  double  (*func)();    // - a function
} value_t;


typedef struct symbol {
  char    *name;        // Symbol Name (identifier)
  short   type;         // Symbol Type (VARINT / VARFLO / PREDEF / UNDEF)
  value_t value;
  struct symbol *next;  // Pointer on the next symbol
} symbol_t,             // Symbol Type Definition
* symbol_ptr_t;         // Symbol List Type Definition

#define SYMBOL_NULL ((symbol_ptr_t) 0)


//Result: point on the new symbol
symbol_ptr_t install(char *tokenName, short tokenType, value_t tokenValue);

//Search a symbol in the symbol list
//Result: pointer on the wanted symbol or NULL if not found
symbol_ptr_t lookUpSymbol(char *tokenName);

// Définir des symboles à l'initialisation : cstes, fcts prédéfinies, mots-clés
void installDefaultSymbols(void);
// Afficher les symboles définis
void printSymbolList(void);

#ifndef _HOC_Y_
#define _HOC_Y_
#include "hoc.tab.h"
#endif
#endif