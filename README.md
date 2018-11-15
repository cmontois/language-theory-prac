# Lex Practice

## How to compile a lex program

```
lex filename.l
gcc lex.yy.c -o execname
```

## Execute

```
./execname args
```

## Exit
Simply press CTRL + D, to exit your program smoothly


## Infos

2 rules for the same length: the priority goes to the first rule

%x permet de définir un état exclusif (qui ne prends pas en compte les autres règles)
```
%x COMMENT
```

## Lex compilation

Create lex.yy.c file + your exe: filename

## Yacc (=Yet Another C Compiler) / Bison (For the Joke :D) compilation

yacc filename.y => y.tab.c
Create y.tab.h file + a file: filename.c

Steps:
1/ Compile .h
2/ Compile lex ?
3/