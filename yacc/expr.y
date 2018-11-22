%{
  #include <stdio.h>
  void yyerror(char *s) {printf("Error: %s",s);}
  int registre[26];
%}
%token INT REG
%token RC AFF PO PF POW INT ADD SUB MUL DIV

%start list
%left ADD SUB /*cette ligne est moins prioritaire que la ligne du dessous*/
%left MUL DIV /*Donc ligne + prioritaire tout en bas (même ligne = même priorité)*/
%nonassoc UNARYMINUS

%%
list:
      | list RC
      | list expr RC {printf("%5d\nexpr>",$2)}
      | list asgn RC
      | list error RC {yyerrok;printf("\nexpr>")}
      ;
expr:  INT {$$=$1;}
      | expr ADD expr   {$$=$1+$3;}
      | expr SUB expr   {$$=$1-$3;}
      | expr MUL expr   {$$=$1*$3;}
      | expr DIV expr   {
          if($3==0) {
            yyerror("Division par 0");
            YYERROR;
          } else {
            $$=$1/$3;
          }
        }
      | expr POW expr   {$$=$1^$3;}
      | SUB expr %prec  UNARYMINUS
      | PO expr PF
      | REG             {$$=registre[$1]}
      | REG AFF expr    {$$=registre[$1]=$3;}
      ;
asgn:  REG AFF expr
      ;
%%

int main() {
  printf("expr>");
  yyparse();/*main calls the parser*/
  return 0;
}