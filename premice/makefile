all: clean first

first:
	lex etatsLex.l
	gcc lex.yy.c -o etatsLex

seconde:
	lex etatsLexBis.l
	gcc lex.yy.c -o etatsLexBis

clean:
	rm -rf lex.yy.c etatsLexBis etatsLex