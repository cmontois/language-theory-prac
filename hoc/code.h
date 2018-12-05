#include <math.h>

//Type de la pile de l'interpreteu
typedef union Data {
    double Value;
    symbol_ptr_t Symb;
} Data;

//Instruction Machine
typedef int (*InsMac) ();
#define STOP (InsMac) 0

/*
 * Prototypes
 */
void Push(Data d);
Data Pop(void);

#define Code2(c1,c2) Code(c1); Code(c2)
#define Code3(c1,c2,c3) Code(c1); Code(c2); Code(c3)

InsMac *Code(InsMac f);
void Execute(InsMac *p);
void NbrPush(void);
void VarPush(void);
void Add(void);
void Sub(void);
void Mul(void);
void Div(void);
void Power(void);
void Negate(void);
void Eval(void);
void Assign(void);
void Print(void);
void Predef(void);
void PrintExpr(void);
void InitCode(void);
void ClrIn(void);