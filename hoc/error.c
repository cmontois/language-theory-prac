#include "hoc.h"

void warning(char * msg, char * msg2) {
    printf("%s %s\n", msg, msg2);
    //    YYERROR;
}
void yyerror(char * msg) {
    printf("SYNTAX-ERROR: [%s]\n", msg);
}

// Verifie le type d'un symbole
void typeCheck(symbol_ptr_t sy, short type, char * msgErr) {
    if (sy->type != type)
        warning(msgErr, sy->name);
}

// Verifie les paramètres d'une opération ou d'une fonction
double errorCheck(double resAppel,  char * msgErr) {
    if (errno != 0) {
        perror(msgErr);
//YYERROR
    }
    return resAppel;
}
