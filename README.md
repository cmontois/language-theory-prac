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