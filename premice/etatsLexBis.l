%{
    int yywrap(void) { printf("Au Revoir\n"); return 1;}
%}

ident   [a-zA-Z][a-zA-Z0-9_]*

/* état commentaire x: états exclusifs (annules les autres règles ?*/
%x COMMENT

%%
"/*"            {printf("£"); BEGIN COMMENT;};
<COMMENT>.|\n   printf("#");// . : tous caractères sauf \n, donc on rajoute \n
<COMMENT>"*/"   {printf("$"); BEGIN INITIAL;};//état INITIAL = état par défaut (donc ici on sort de l'état commentaire avec */ pour revenir à l'état normal)

"quit"          {printf("mot cle: quit\n"); };
{ident}         {printf("identifiant: %s\n", yytext); };
<<EOF>>         return 1;
%%

int main() {
  yylex();
  return 0;
}