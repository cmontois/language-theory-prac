%{
  #include "expr.tab.h"
%}

/*This option allows your compilation not to fail without the yywrap function*/
%option noyywrap

po          "("
pf          ")"
aff         "="
integer     [1-9][0-9]*|0
NL          \n
operator    [-+*/]
minus       [a-z]
majuscule   [A-Z]
lettre      ({minus}|{majuscule})

%%
{integer}     {yylval=atoi(yytext);return INT;};/*NBR will be defined in the expr.h (tag: %token NBR)*/
{NL}          {return RC;};
"+"           {return ADD;};
"-"           {return SUB;};
"*"           {return MUL;};
"/"           {return DIV;};
"^"           {return POW;};
{minus}       {return yytext[0]-'a';return REG;};
{majuscule}   {return yytext[0]-'A';return REG;};
.             ;/*Avoid repetition for everything which hasn't been defined*/
<<EOF>>       {return 1;};
%%