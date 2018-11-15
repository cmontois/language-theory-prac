%{
  #include "expr.tab.h"
%}

/*This option allows your compilation not to fail without the yywrap function*/
%option noyywrap

integer     [1-9][0-9]*
NL          \n
operator    [-+*/]

%%
{integer}     {yylval=atoi(yytext);return NBR;};/*NBR will be defined in the expr.h (tag: %token NBR)*/
{NL}          return RC;
{operator}    return yytext[0];
.             ;/*Avoid repetition for everything which hasn't been defined*/
<<EOF>>       return 1;

%%