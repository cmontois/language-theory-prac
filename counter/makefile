all: clean counter

counter:
	lex counter.l
	gcc lex.yy.c -o counter

example: 
	lex example.l
	gcc lex.yy.c -o example

clean:
	rm -rf lex.yy.c counter example