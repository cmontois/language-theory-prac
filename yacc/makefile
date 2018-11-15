all: clean expr-bison

# You can use yacc or bison (bison just change the name of the compiled file TODO CHECK)
expr-yacc:
	yacc -d expr.y
	lex expr.l
	gcc y.tab.c lex.yy.c -o expr

expr-bison:
	bison -d expr.y
	lex expr.l
	gcc expr.tab.c lex.yy.c -o expr


clean:
	rm -rf y.tab.c y.tab.h expr.tab.c expr.tab.h lex.yy.c