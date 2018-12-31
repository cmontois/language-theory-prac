%{
    #include "hoc.h"
    #include <math.h>
    #include "code.h"

    void prompt(void);

    extern InsMac Prog[];
    extern InsMac *ProgPtr;
    extern InsMac *BaseProg;

%}

/*********_********_*********_********_*********_********_***********/
/*                      Entités, Associativité, Axiome, ....        */
/*********_********_*********_********_*********_********_***********/
/* Redéfinition de YYSTYPE = type de la variavle yylval             */
/* yylval porte la valeur du token reconnu par l'AL                 */
%union {
    int     iValue;          // nombre entier
    double  fValue;          // nombre réel
    symbol_ptr_t symbol;     // identifiant : var,
}
// Déclaration des tokens valués avec le type adéquat
%token <symbol>  NUMINT
%token <symbol>  NUMFLO
%token <symbol>  VARINT VARFLO CSTFLO PREDEF UNDEF
// Déclaration des tokens non-valués
%token PRINT PRINTS PRINTP PRINTPI
//Typage des unités syntaxiques
%type  <fValue> expr asgn
/* Associativité à gauche de même priorité */
%left  '+' '-'
/* Associativité à gauche de priorité superieure */
%left  '*' '/'
// Surcharge de l'opération soustraction par le signe
%left  UNARYMINUS
//Associativité à droite
%right '#'

/*********_********_*********_********_*********_********_***********/
/* Debut de la grammaire */
/*********_********_*********_********_*********_********_***********/

%%
list:   vide
    | list '\n'                         { prompt(); }
    | list asgn '\n'                    { Code(STOP); return 1;}
    | list expr '\n'                    { Code2(Print, STOP); return 1; }
    | list error '\n'                   { yyerrok; prompt(); }
    ;

vide:   ;

varAsgn: VARINT                         { Code2(VarPush, (InsMac) $1); }
    | VARFLO                            { Code2(VarPush, (InsMac) $1); }
    | UNDEF                             { Code2(VarPush, (InsMac) $1); }
    ;
asgn: varAsgn '=' expr                  { Code(Assign); }
    ;

expr: NUMINT                            { Code2(NbrPush, (InsMac) $1); }
    | NUMFLO                            { Code2(NbrPush, (InsMac) $1); }
    | VARINT                            {
            typeCheck($1, VARINT, "Undefined variable or is not integer");
            Code3(VarPush, (InsMac) $1, Eval);
        }
    | VARFLO                            {
            typeCheck($1, VARFLO, "Undefined variable");
            Code3(VarPush, (InsMac) $1, Eval);
        }
    | CSTFLO                            {
            typeCheck($1, CSTFLO, "Undefined constante");
            Code2(NbrPush, (InsMac) $1);
        }
    | '(' expr ')'                      { $$ = $2; }
    | expr '+' expr                     { Code(Add); }
    | expr '-' expr                     { Code(Sub); }
    | expr '*' expr                     { Code(Mul); }
    | expr '/' expr                     {
            if ($3 == 0.0) warning("Division par zéro", "FPE");
            Code(Div);
        }
    | expr '#' expr                     { Code(Power); }
    | '-' expr %prec UNARYMINUS         { $$ = -$2; }
    | PREDEF '(' expr ')'               {
            typeCheck($1, PREDEF, "Undefined fonction");
            Code2(Predef,(InsMac)$1->value.func); 
        }
	| PRINTS                            { Code((InsMac)printSymbolList);}
	| PRINTP                            { Code ((InsMac) printProg);}
	| PRINTPI                           { Code ((InsMac) printPile);}
    ;
%%

/*********_********_*********_********_*********_********_***********/
/*                          Programme principal                     */
/*********_********_*********_********_*********_********_***********/
// Gestion des erreurs :
char *progName;     // Contient le nom du programme
int lineNo = 0;     // Indique la ligne courante

int main (int argc, char *argv[])          /* Appel de l'AS  */
{
    progName = argv[0];
    fprintf(stdout,"Welcome to the basic calculator.\nImplemented by Clement Montois.\nVersion 1.0\n");
    installDefaultSymbols();

    for (InitCode(); yyparse(); InitCode()) Execute(BaseProg);

    fprintf(stdout, "Logout.\nSee you ! !!\n");
    exit(EXIT_SUCCESS);
}

void prompt (void)
{
    lineNo++;
    fprintf(stdout, "hoc> ");
}
