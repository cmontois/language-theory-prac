%{
    int yywrap(void) { printf("Au Revoir\n"); return 1;}
%}

%%
"a"     {printf("1"); };
"aa"    {printf("2"); };
%%
int main() {
  yylex();
  return 0;
}


//How to compile
//lex etatsLex.l
//gcc lex.yy.c -o etatsLex