#include "hoc.h"

void warning (char * msg, char * msg2) {
  printf("%s %s\n", msg, msg2);
}

void yyerror (char * msg) {
  printf("SYNTAX-ERROR: [%s]\n", msg);
}

/**
 * Check Symbol Type
 */
void typeCheck(symbol_ptr_t symbol, short type, char * msgErr) {
  if(symbol->type != type) {
    warning(msgErr, symbol->name);
  }
}

/**
 * Check Symbol Parameters
 */
double errorCheck(double result, char * msgErr) {
  if(errno != 0) {
    perror(msgErr);
  }
  return result;
}