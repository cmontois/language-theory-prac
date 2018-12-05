%{
    #include <string.h>
    #include "symbol.h"
    #include "hoc.tab.h"
    #define _HOC_Y_
%}

%%

[ \t]                           {;};
[0-9]+                          {yylval.symbol = install("", NUMFLO, atof(yytext); return NUMINT;};
[0-9]+\.?[0-9]*\.?[0-9]+        {yylval.symbol = install("", NUMFLO, atof(yytext); return NUMFLO;};
"PRINT"                         {return PRINT;};

[a-zA-Z][a-zA-Z0-9]*  {
    symbol_ptr_t sp;
    if ((sp = lookUpSymbol(yytext)) == SYMBOL_NULL) {
        sp = install(yytext, UNDEF, (value_t)0);
    }
    yylval.symbol = sp; return sp->type;
};

\n                              { return '\n'; };
.                               { return yytext[0]; };
<<EOF>>                           return 0;
%%
