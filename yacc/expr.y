%{
  #include <stdio.h>
  void yyerror(char *s) {printf("Non authorized");}
%}
%token RC NBR

%start list
%%
list:
      | list expr RC {printf("%5d\nexpr>",$2)}
      | list RC
      ;
expr:   NBR            {$$=$1;}
      | expr '-' expr {$$=$1-$3;}
      | expr '+' expr {$$=$1+$3;}
      | expr '*' expr {$$=$1*$3;}
      | expr '/' expr {$$=$1/$3;}
    ;
%%

//$$ = $1 + $3


int main() {
  printf("expr>");
  yyparse();/*main calls the parser*/
  return 0;
}