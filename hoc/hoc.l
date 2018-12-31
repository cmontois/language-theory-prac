%{
    #include <string.h>
    #include "symbol.h"
    #include "hoc.tab.h"
    #define _HOC_Y_
%}

%%
[ \t]       {;};
[0-9]+      { 
                value_t v; v.iValue = atoi(yytext);
                yylval.symbol = installSymbol("", NUMINT, v);
                #ifdef DEBUG_L
                printf("\033[36mToken reconnu de type [%d] avec la valeur [%d]\n\033[%30m", NUMINT, v.iValue);
                #endif
                return NUMINT; 
            };

[0-9]+\.?|[0-9]*\.[0-9]+ {
                value_t v; v.fValue = atof(yytext);
                yylval.symbol = installSymbol("", NUMFLO, v);
                return NUMFLO; 
            }
"PRINT"     { return PRINT; };
"$"         { return PRINTS; };
"@"         { return PRINTP; };
"&"		    { return PRINTPI;};
[a-zA-Z][a-zA-Z0-9]*  {
                symbol_ptr_t sp;
                if ((sp = lookUpSymbol(yytext)) == SYMBOL_NULL)
                sp = installSymbol(yytext, UNDEF, (value_t)0);
                yylval.symbol = sp; return sp->type ; 
			    #ifdef DEBUG
                printf("%sVariable reconnu de type [%hd]\n%s",KGRN, sp->type,KNRM);
                #endif
			    return sp->type ;
            };
\n          { return '\n'; };
.           { return yytext[0]; };
%%
