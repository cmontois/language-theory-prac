#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
extern int errno;

#include "symbol.h"
/* Installe les constantes et predefs */
void installDefaultSymbols(void);

void warning(char * msg, char * msg2);
void yyerror(char * msg);

void typeCheck(symbol_ptr_t symbol, short type, char * msgErr);
double errorCheck(double result, char * msgErr);

#ifndef _HOC_Y_
#define _HOC_Y_
#include "hoc.tab.h"
#endif
