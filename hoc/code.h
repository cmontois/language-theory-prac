#include <math.h>

typedef union Data {         /* Type de la pile de l'interpreteur */
    double Value;
    symbol_ptr_t Symb;
} Data;

typedef int (*InsMac) ();   /* Instruction Machine */
#define STOP (InsMac) 0
#define Code2(c1, c2)         Code(c1); Code(c2)
#define Code3(c1, c2, c3)     Code(c1); Code(c2); Code(c3)

/*
 * Prototypes
 */
InsMac *Code(InsMac f);
void Execute(InsMac *p);
void Push(Data d);
Data Pop(void);
// void printTable(void);
void printProg(void);
void printPile(void);
int NbrPush(void);
int VarPush(void);
int Add(void) ;
int Sub(void) ;
int Mul(void);
int Div(void);
int Power(void) ;
int Negate(void);
int Eval(void);
int Assign(void) ;
int Print(void) ;
int Predef(void);
int PrintExpr(void);
int InitCode(void);
int ClrIn(void);
