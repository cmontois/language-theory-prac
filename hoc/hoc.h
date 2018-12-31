#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "color.h"
#include "symbol.h"

extern int errno;

/* Installe les constantes et predefs */
void installDefaultSymbols(void);

void yyerror(char * msg);
void warning(char * msg, char * msg2);

void typeCheck(symbol_ptr_t sy, short type, char * msgErr);
double errorCheck(double resAppel,  char * msgErr);
#ifndef _HOC_Y_
#define _HOC_Y_
#include "hoc.tab.h"
#endif
