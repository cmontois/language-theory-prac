make: clean hoc.tab.c hoc.tab.h lex.yy.c hoc

hoc.tab.c: hoc.y
	bison hoc.y

hoc.tab.h: hoc.y
	bison -d hoc.y

lex.yy.c: hoc.l
	lex hoc.l

hoc : hoc.tab.c lex.yy.c
	echo "Running compilation ..."
	gcc hoc.tab.c lex.yy.c -o hoc symbol.c init.c error.c code.c -ll -ly -lm -D DEBUG_L -D DEBUG_C -D DEBUG
	echo "Compilation successfully completed..."

clean:
	echo "Cleaning directory ..."
	rm -rf lex.yy.c hoc.tab.c hoc.tab.h hoc code.o