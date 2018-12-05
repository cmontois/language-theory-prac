make: clean hoc

hoc:
	bison -d hoc.y
	lex  hoc.l
	gcc -o hoc hoc.tab.c lex.yy.c symbol.c init.c error.c code.c -ll -ly

clean:
	rm -rf lex.yy.c hoc.tab.c hoc.tab.h hoc code.o

code:
	gcc -c code.c