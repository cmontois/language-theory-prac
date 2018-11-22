file.l = analyseur lexical

%token ->

```
yylex()
```
return le num de token actuel et 1 value éventuelle dans yylval (est de type YYSTYPE) par défaut YYSTYPE est un int

YY   = Yacc
S    = Symbol
TYPE = Type

La valeur sera stocké dans le registre associé au token reconnu dans une règle syntaxique