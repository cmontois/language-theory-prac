# HOC High Order Calculator

Compile the program:

```
make
```

Clean your working directory:

```
make clean
```

Example with defined constants (v0.0.2):
```
Welcome to the basic calculator.
Implemented by Clément Montois LA3 ;).
Version 0.2
Loading: Float Constants
Loading: Float Functions
Donehoc> PI
= 1.4137541e+09
hoc> GAMMA
= -59787751
hoc>
```

Error: wrong constant value

## LIFO

pile d'execution qui permet d'évaluer notre programme

exemple de programme:

id1 = 2 * id2

- empiler constante de valeur 2
- empiler variable id2
- évaluer la variable id2
- multiplier id2 par 2
- empiler variable id1
- affecter la variable id1
- arrêter

## Symbol Table

TODO:

Pour les nombres, le code associé sera de ranger le pointeur sur le symbole :

NbrPush()

- Il en est de même pour les variables avec une opération d’évaluation ou
d’assignation :

VarPush(), Eval(), Assign()

- Pour les fonctions prédéfinies, on range l’adresse de la fonction :

Predef()

-  Pour les opérations, on considère que la pile de données contient les opérandes nécessaires pour effectuer l’opération. On dépile alors les
opérandes, on effectue l'opération et on empile le résultat.

Add(), Sub(), Mul(), Div(), Power(), Negate(),


## CHANGELOG

[0.0.1]

- simple high order calculator

[0.0.2]

- error management (error.c)

[0.0.3]

- LIFO lifo data ?  (Last In Firt Out)
- manage this a = a * 2 