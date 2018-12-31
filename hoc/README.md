# High Order Calculator

[Github Repository](https://github.com/cmontois/language-theory-prac/tree/master/hoc)

## Objectives v1.0

> trace al    //DEBUG_L = Analyse Lexicale 
> trace Code  // Code
> trace all   // all
> trace as    // ana syntaxique
> trace exe   // exe

```
    | PRINT { Code(printSymbolList); $$=0; }
```

### Done

Manage Constant like PI:

```
hoc> PI
@PROG=[0x10a51e2f0x] avec @CODE=[0x10a51c6f0x]
@PROG=[0x10a51e2f8x] avec @CODE=[0x7fb858c02b90x]
@PROG=[0x10a51e300x] avec @CODE=[0x10a51cac0x]
@PROG=[0x10a51e308x] avec @CODE=[0x0x]
|  TYPE  | NUMINT | NUMFLO |
|     262|     258|     259|
= 3.1415927
@PROG=[0x10a51e2f0x]    #PILE=[0x10a5221e0x]
```

Manage function like log

```
hoc> log(4)
Token reconnu de type [258] avec la valeur [4]
@PROG=[0x1002322f0x] avec @CODE=[0x1002306f0x]
@PROG=[0x1002322f8x] avec @CODE=[0x7fe2b9d00000x]
@PROG=[0x100232300x] avec @CODE=[0x100230b00x]
@PROG=[0x100232308x] avec @CODE=[0x1002301f0x]
@PROG=[0x100232310x] avec @CODE=[0x100230ac0x]
@PROG=[0x100232318x] avec @CODE=[0x0x]
|  TYPE  | NUMINT | NUMFLO |
|     258|     258|     259|
= 1.3862944
@PROG=[0x1002322f0x]    #PILE=[0x1002361e0x]
```

Manage Syntax Error (example: not existing function)

```
hoc> unexistingfunction(4)
@PROG=[0x100232300x] avec @CODE=[0x1002307b0x]
@PROG=[0x100232308x] avec @CODE=[0x7fe2b9e000b0x]
SYNTAX-ERROR: [syntax error]
Token reconnu de type [258] avec la valeur [4]
```


Variable assignement:

```
hoc> a=4
@PROG=[0x10a4c42f0x] avec @CODE=[0x10a4c2610x]
@PROG=[0x10a4c42f8x] avec @CODE=[0x7fd647e002b0x]
Token reconnu de type [258] avec la valeur [4]
@PROG=[0x10a4c4300x] avec @CODE=[0x10a4c25a0x]
@PROG=[0x10a4c4308x] avec @CODE=[0x7fd647e002e0x]
@PROG=[0x10a4c4310x] avec @CODE=[0x10a4c2910x]
@PROG=[0x10a4c4318x] avec @CODE=[0x0x]
VARFLOAssignation de  [4] à la variable [a]
@PROG=[0x10a4c42f0x]    #PILE=[0x10a4c81e0x]
hoc> a
@PROG=[0x10a4c42f0x] avec @CODE=[0x10a4c2610x]
@PROG=[0x10a4c42f8x] avec @CODE=[0x7fd647e002b0x]
@PROG=[0x10a4c4300x] avec @CODE=[0x10a4c2860x]
@PROG=[0x10a4c4308x] avec @CODE=[0x10a4c2a40x]
@PROG=[0x10a4c4310x] avec @CODE=[0x0x]
Evaluation de  [a]
= 4
@PROG=[0x10a4c42f0x]    #PILE=[0x10a4c81e0x]
```

Print code table (using @)

```
hoc> @
@PROG=[0x10a51e2f0x] avec @CODE=[0x10a51cc50x]
@PROG=[0x10a51e2f8x] avec @CODE=[0x10a51cac0x]
@PROG=[0x10a51e300x] avec @CODE=[0x0x]
Table de code:
-----------------------------------
|      FUNC      |     ADDRESS    |
-----------------------------------
|    NbrPush     | 0x10a51de71 |
|    VarPush     | 0x10a51de79 |
|        Add     | 0x10a51de81 |
|        Sub     | 0x10a51de85 |
|        Mul     | 0x10a51de89 |
|        Div     | 0x10a51de8d |
|      Power     | 0x10a51de91 |
|     Negate     | 0x10a51de97 |
|       Eval     | 0x10a51de9e |
|     Assign     | 0x10a51dea3 |
|      Print     | 0x10a51deaa |
|     Predef     | 0x10a51deb0 |
|  PrintExpr     | 0x10a51deb7 |
|   InitCode     | 0x10a51dec1 |
|      ClrIn     | 0x10a51deca |
-----------------------------------
Instruction [0x10a51cc50] installée en [0x10a51e2f0]
Instruction [0x10a51cac0] installée en [0x10a51e2f8]
Instruction [0x0] installée en [0x10a51e300]
Instruction [0x7fb858e00090] installée en [0x10a51e308]
Instruction [0x10a51c8e0] installée en [0x10a51e310]
Instruction [0x10a51cac0] installée en [0x10a51e318]
Instruction [0x0] installée en [0x10a51e320]
Instruction [0x0] installée en [0x10a51e328]
-----------------------------------
Stack empty (pop) (null)
= 0
@PROG=[0x10a51e2f0x]    #PILE=[0x10a5221e0x]
```

Print Fifo (using &)

```
hoc> &
@PROG=[0x10a51e2f0x] avec @CODE=[0x10a51ce80x]
@PROG=[0x10a51e2f8x] avec @CODE=[0x10a51cac0x]
@PROG=[0x10a51e300x] avec @CODE=[0x0x]
Pile de données:
Data value : [3.000000]
Data value : [5.000000]
Data value : [0.000000]
Data value : [0.000000]
Data value : [0.000000]
Data value : [0.000000]
Data value : [0.000000]
Data value : [0.000000]
Stack empty (pop) (null)
= 0
@PROG=[0x10a51e2f0x]    #PILE=[0x10a5221e0x]
```

Print variables (using $)

```
hoc> $
@PROG=[0x101a032f0x] avec @CODE=[0x101a00e70x]
@PROG=[0x101a032f8x] avec @CODE=[0x101a01aa0x]
@PROG=[0x101a03300x] avec @CODE=[0x0x]
Constantes:
        PHI     = 1.618034
        DEG     = 57.29578
        GAMMA   = 0.57721566
        E       = 2.7182818
        PI      = 3.1415927
Variables Réelles:
Variables Entières:

Non définis :

Stack empty (pop) (null)
= 0
@PROG=[0x101a032f0x]    #PILE=[0x101a071e0x]
```

### TODO / IN PROGRESS

Manage DEBUG_L, DEBUG_C, ... instead of only one DEBUG option