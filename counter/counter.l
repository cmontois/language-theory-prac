%{
    int yywrap(void) { printf("File read !\n"); return 1;}
    int  numchars = 0;
    int  numwords = 0;
    int  numlines = 0;
%}

%%

[\n]        { numchars++;  numlines++;         }
[\r]        { numchars++;                      }
[^ \t\n]+   { numwords++;  numchars += yyleng; }
.           { numchars++;                      }

%%


int main (int argc, char *argv[]) {
  if (argc == 2) {
    if ((yyin=fopen(argv[1],"r"))) {
      (void) yylex();
      fclose(yyin);
      printf("lines: %5d\n", numlines);
      printf("chars: %5d\n", numchars);
      printf("words: %5d\n", numwords);
      return(0);
    }
    else {
      printf("File not found !\n");
      exit(1);
    }
  }
  else {
    if(argc > 2) {
      printf("Too many arguments\n");
    } else {
      printf("One argument is missing\n");
    }
  }
  return(0);
}