//MANIPULATION DES DIFFERENTES STRUCURES

#include <stdio.h>
#include "hoc.h"
#include "hoc.tab.h"
#include "code.h"

#define MAXSTACK 256         /* Taille Max de la Pile */
static Data Stack[MAXSTACK]; /* La pile */
static Data *StackPtr;       /* Prochain emplacement libre */

#define MAXPROG 2000         /* Taille max d'un prog */
InsMac Prog[MAXPROG];        /* La machine d'execution */
InsMac *ProgPtr;             /* Prochain emplacement libre */
InsMac *PC;                  /* Compteur d'execution */
InsMac *BaseProg;            /* Debut de sous programme */
int    Returning;            /* 1 si return a ete vu */

// MANIPULATION DE LA PILE DES DONNEES

/**
 * Stocke d en sommet de pile
 */ 
void Push(Data d) {
  if (StackPtr >= &Stack[MAXSTACK]) warning("Stack Overflow (push)", NULL);
  *StackPtr++ = d;
}

/**
 * Extrait le sommet de la pile
 */ 
Data Pop(void) {
  if (StackPtr <= Stack) warning("Stack empty (pop)", NULL);
  return *--StackPtr;
}

//MANIPULATION DE LA PILE DES INSTRUCTIONS

/**
 * Installe une instruction machine
 */ 
InsMac *Code(InsMac f)
{    
  InsMac *Localisation = ProgPtr;

  if (ProgPtr >= &Prog[MAXPROG]) warning("Bigest program (code)", NULL);
  *ProgPtr++ = f;
  return Localisation;
}

/**
 * Execute le programme p
 */ 
void Execute(InsMac *p) {
  for (PC = p; *PC != STOP && !Returning; ) (*(*PC++)) ();
}

//CODES ASSOCIES AVEC LES EXPR ALGEBRIQUES

/**
 * Range un nombre
 */ 
void NbrPush(void) {
  Data d;
  d.Value = ((symbol_ptr_t) *PC++)->value.fValue;
  Push(d);
}

/**
 * Range une variable
 */
void VarPush(void) {   
  Data d;
  d.Symb = ((symbol_ptr_t) *PC++);
  
  if ((d.Symb)->type != VARFLO && d.Symb->type != UNDEF) warning("(VarPush) not a variable", d.Symb->name);
  Push(d);
}

//OPERATEURS ARITHMETIQUES REELLES

/**
 * Addition
 */
void Add(void) {   
  Data d2 = Pop(), d1 = Pop();
  d1.Value = d1.Value + d2.Value;
  Push(d1);
}

/**
 * Soustraction
 */
void Sub(void) {   
  Data d2 = Pop(), d1 = Pop();
  d1.Value = d1.Value - d2.Value;
  Push(d1);
}

/**
 * Multiplication
 */
void Mul(void) {   
  Data d2 = Pop(), d1 = Pop();
  d1.Value = d1.Value * d2.Value;
  Push(d1);
}

/**
 * Division
 */
void Div(void) {   
  Data d2 = Pop(), d1 = Pop();
  if (d2.Value == 0.0) warning("(Div) division by zero", NULL);
  d1.Value = d1.Value / d2.Value;
  Push(d1);
}

/**
 * Puissance
 */
void Power(void) {   
  Data d2 = Pop(), d1 = Pop();

  d1.Value = pow(d1.Value, d2.Value);
  Push(d1);
}

/**
 * Oppose
 */
void Negate(void) {   
  Data d = Pop();
  d.Value = - d.Value;
  Push(d);
}

//EVALUATION ET AFFECTATION VARFLO REELLE

/**
 * Evaluation
 */
void Eval(void) {   
  Data d = Pop();
  if (d.Symb->type == UNDEF) warning("(Eval) undefined variable", d.Symb->name);
  d.Value = d.Symb->value.fValue;
  Push(d);
}

/**
 * Assignation
 */
void Assign(void) {   
  Data d1 = Pop(), d2 = Pop();
  if (d1.Symb->type != VARFLO && d1.Symb->type != UNDEF) warning("(Assign) can't assign", d1.Symb->name);
  d1.Symb->value.fValue = d2.Value;
  d1.Symb->type    = VARFLO;
}

//RESULTAT D'UNE EXPRESSION ALGEBRIQUE

/**
 * Affichage du resultat d'une expression
 */
void Print(void) {   
  Data d = Pop();
  printf("= %.8g\n", d.Value);
}

/**
 * Evalue une fonction predefinie
 */
void Predef(void) {   
  Data d = Pop();
  d.Value = (*(double (*)()) (*PC++)) (d.Value);
  Push(d);
}

/**
 * Affichage d'une expression
 */
void PrintExpr(void) {
  Data d;
  d = Pop();
  printf("%.8g\n", d.Value);
}

void InitCode(void) {
  StackPtr  = Stack;
  ProgPtr   = BaseProg;
  // Fp        = Frames;
  Returning = 0;
  fprintf(stdout, "hoc> ");
}

//LECTURE DES DONNEES

/**
 * Traitement d'une erreur de syntaxe
 */
void ClrIn(void) {
  warning("syntax error", NULL);
  fprintf(stdout, "hoc> ");
}