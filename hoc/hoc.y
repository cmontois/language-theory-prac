%{
      #include "hoc.h"
      #include "code.h"
      #include <math.h>
      void prompt(void);

      extern InsMac Prog[];
      extern InsMac *ProgPtr;
      extern InsMac *Code();
      extern InsMac *BaseProg;
%}

%union {
  int           iValue; //nbr entiers
  double        fValue; //nbr reels
  symbol_ptr_t  symbol; //identifiant
}

// Déclaration tokens valués avec le type adéquat
%token <symbol>    NUMINT
%token <symbol>    NUMFLO
%token <symbol>    VARINT VARFLO PREDEF UNDEF  CSTFLO

// Déclaration tokens non valués
%token PRINT

// Typage des unités syntaxiques
%type <fValue> expr asgn

// Associativité gauche même prio
%left '+' '-'
// Associativité gauche prio sup
%left '*' '/'
// Surcharge op soustraction par le signe (nbr negatif)
%left UNARYMINUS
// Associativité droite
%left '#'

%%
list:   /* Vide */
      | list '\n'                               { prompt();}
      | list asgn '\n'                          { Code(STOP);return 1;}
      | list expr '\n'                          { Code2(Print, STOP); return 1;}
      | list error '\n'                         { yerrok; prompt(); }
      ;

varAsgn:VARINT                                  { Code2(VarPush, (InsMac) $1); }
      | VARFLO                                  { Code2(VarPush, (InsMac) $1); }
      | UNDEF                                   { Code2(VarPush, (InsMac) $1); }
      ;
asgn:   varAsgn "=" expr                        { Code3(VAssign); }
      ;
expr:   NUMINT                                  { $$ = (double) $1; }
      | NUMFLO                                  { Code(NbrPush, (InsMac) $1); }
      | VARINT {
            typeCheck($1, VARINT, "Undefined variable or not an integer");
            $$ = (double) $1->value.iValue;
      }
      | VARFLO {
            typeCheck($1, VARFLO, "Undefined variable");
            $$ = $1->value.iValue;
      }
      | CSTFLO {
            typeCheck($1, CSTFLO, "Undefined constante");
            Code3(NbrPush, (InsMac) $1, Eval);
            $$ = $1->value.iValue;
      }
      | '(' expr ')'                            { Code(Add); }
      | expr '+' expr                           { Code(Sub); }
      | expr '-' expr                           { Code(Mul); }
      | expr '*' expr                           { Code(Div); }
      | expr '/' expr  {
            if ($3 == 0.0) warning("Division par zéro", "FPE");
            $$ = $1 / $3;
      }
      | expr '#' expr                           { Code(Power); }
      | '-' expr %prec UNARYMINUS               { Code(Negate); }
      | PREDEF '(' expr ')' {
            typeCheck($1, PREDEF, "Undefined function");
            $$ = (*($1->value.func))($3);
      }
;
%%

// Gestion des erreurs
char *progName;     // Contient le nom du programme
int lineNo = 0;     // Indique la ligne courante

int main (int argc, char *argv[])          /* Appel de l'AS  */
{
      progName = argv[0];
      fprintf(stdout,"Welcome to the basic calculator.\nImplemented by Clément Montois LA3 ;).\nVersion 0.2\n");
      installDefaultSymbols();
      prompt();
      //yyparse(); /* yyparse() a besoin de yylex() */
      for(InitCode(); yyparse(); InitCode()) {
            Execute(BaseProg);
      }
      fprintf(stdout, "logout\nsee ya !\n");
      exit(EXIT_SUCCESS);
}

void prompt (void)
{
      lineNo++;
      fprintf(stdout, "hoc> ");
}