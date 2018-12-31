/*********_********_*********_********_*********_********_*********_*******/
/* MANIPULATION DES DIFFERENTES STRUCURES    */
/*********_********_*********_********_*********_********_*********_*******/
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

/*********_********_*********_********_*********_********_*********_*******/
/* MANIPULATION DE LA PILE DES DONNEES       */
/*********_********_*********_********_*********_********_*********_*******/
void Push(Data d)                      /* Stocke d en sommet de pile */
{
    if (StackPtr >= &Stack[MAXSTACK]) warning("Stack Overflow (push)", NULL);
    *StackPtr++ = d;
}

Data Pop(void)                   /* Extrait le sommet de la pile */
{
    if (StackPtr <= Stack) warning("Stack empty (pop)", NULL);
    return *--StackPtr;
}
/*********_********_*********_********_*********_********_*********_*******/
/* MANIPULATION DE LA PILE DES INSTRUCTIONS  */
/*********_********_*********_********_*********_********_*********_*******/
InsMac *Code(InsMac f)              /* Installe une instruction machine */
{   
    InsMac *Localisation = ProgPtr;
    if (ProgPtr >= &Prog[MAXPROG]) warning("Bigest program (code)", NULL);
    *ProgPtr++ = f;
    #ifdef DEBUG_C
    printf("\033[32m@PROG=[%px] avec @CODE=[%px]\n\033[%30m", Localisation, f);
    #endif
    return Localisation;
}

void Execute(InsMac *p)                   /* Execute le programme p */

{
    for (PC = p; *PC != STOP && !Returning; ) (*(*PC++)) ();
}
/*********_********_*********_********_*********_********_*********_*******/
/* CODES ASSOCIES AVEC LES EXPR ALGEBRIQUES  */
/*********_********_*********_********_*********_********_*********_*******/

/**
 * Range un nombre
 */
int NbrPush(void)
{
    Data d;
	symbol_ptr_t sp=(symbol_ptr_t)*PC++;
	if(sp->type==NUMINT)
		d.Value = sp->value.iValue;
	else 
		d.Value=sp->value.fValue;
	
    Push(d);
	return 0;
}

/**
 * Range une variable
 */
int VarPush()
{
    Data d;
	symbol_ptr_t sp = ((symbol_ptr_t) *PC++);
    
    if (sp->type != VARFLO && sp->type != UNDEF && sp->type != VARINT) 
		warning("(VarPush) not a variable", d.Symb->name);
	d.Symb=sp;
	
    Push(d);
	return 0;
}

/**
 * OPERATEURS ARITHMETIQUES REELLES
 */

/**
 * Addition
 */
int Add(void)
{
    Data d2 = Pop(), d1 = Pop();
    d1.Value = d1.Value + d2.Value;
    Push(d1);
    return 0;
}

/**
 * Soustraction
 */
int Sub(void)
{
    Data d2 = Pop(), d1 = Pop();
    d1.Value = d1.Value - d2.Value;
    Push(d1);
    return 0;
}

/**
 * Multiplication
 */
int Mul(void)
{
    Data d2 = Pop(), d1 = Pop();
    d1.Value = d1.Value * d2.Value;
    Push(d1);
    return 0;
}

/**
 * Division
 */
int Div(void)
{
    Data d2 = Pop(), d1 = Pop();
    if (d2.Value == 0.0) warning("(Div) division by zero", NULL);
    d1.Value = d1.Value / d2.Value;
    Push(d1);
    return 0;
}

/**
 * Puissance
 */
int Power(void)
{
    Data d2 = Pop(), d1 = Pop();
    
    d1.Value = pow(d1.Value, d2.Value);
    Push(d1);
    return 0;
}

/**
 * Oppose
 */
int Negate(void)
{
    Data d = Pop();
    d.Value = - d.Value;
    Push(d);
    return 0;
}

/**
 * EVALUATION ET AFFECTATION VAR REELLE 
 */

/**
 * Evaluation
 */
int Eval(void)
{
    Data d = Pop();
	
	#ifdef DEBUG
		printf("%sEvaluation de  [%s] \n%s", KGRN, d.Symb->name,KNRM);
	#endif
	
    if (d.Symb->type == UNDEF) warning("(Eval) undefined variable", d.Symb->name);
	if(d.Symb->type==VARINT)
		d.Value = d.Symb->value.iValue;
	else
		d.Value = d.Symb->value.fValue;
	
    Push(d);
    return 0;
}

/**
 * Assignation
 */
int Assign(void)
{
	Data d1 = Pop(), d2 = Pop();
	if(d2.Symb->type==UNDEF) printf("VARFLO");
    if (d2.Symb->type != VARINT && d2.Symb->type != UNDEF) warning("(Assign) can't assign", d2.Symb->name);
	if(d2.Symb->type==VARFLO) {
		d2.Symb->value.fValue = d1.Value;
		d2.Symb->type    = VARFLO;
		#ifdef DEBUG
		printf("%sAssignation de  [%f] à la variable [%s] \n%s", KGRN, d2.Symb->value.fValue,d2.Symb->name,KNRM);
		#endif
	}
	else {
		d2.Symb->value.iValue = d1.Value;
		d2.Symb->type    = VARINT;
		#ifdef DEBUG
		printf("%sAssignation de  [%d] à la variable [%s]  \n%s", KGRN, d2.Symb->value.iValue,d2.Symb->name,KNRM);
		#endif
    }
	
	return 0;
}

/**
 * RESULTAT D'UNE EXPRESSION ALGEBRIQUE
 */

/**
 * Affichage du resultat d'une expression
 */
int Print(void)
{
    Data d = Pop();
    printf("= %.8g\n", d.Value);
    return 0;
}

/**
 * Evalue une fonction predefinie
 */
int Predef(void)
{
    Data d = Pop();
    d.Value = (*(double (*)()) (*PC++)) (d.Value);
    Push(d);
    return 0;
}

/**
 * Affichage d'une expression
 */
int PrintExpr(void)
{
    Data d;
    d = Pop();
    printf("%.8g\n", d.Value);
    return 0;
}

/**
 *
 */
int InitCode(void)
{
    StackPtr  = Stack;
    ProgPtr   = BaseProg = Prog;
    Returning = 0;
    #ifdef DEBUG_C
    printf("\033[31m@PROG=[%px]\t#PILE=[%px]\n\033[%30m", ProgPtr, StackPtr);
    #endif
    fprintf(stdout, "hoc> ");
    return 0;
}

/**
 * LECTURE DES DONNEES
 */

/**
 * Traitement d'une erreur de syntaxe
 */
int ClrIn(void)
{
    warning("syntax error", NULL);
    fprintf(stdout, "hoc> ");
    return 0;
}

/**
 * Affichage de la table de code
 */
void printProg(void){
	printf("%sTable de code:\n%s",KBLU,KNRM);
	char* functs[15] = {"NbrPush","VarPush","Add","Sub","Mul","Div","Power","Negate","Eval","Assign","Print","Predef","PrintExpr","InitCode","ClrIn"};
    printf("%s-----------------------------------\n%s",KBLU,KNRM);
    printf("%s|      FUNC      |     ADDRESS    |\n%s",KBLU,KNRM);
    printf("%s-----------------------------------\n%s",KBLU,KNRM);
    for(int p=0; p<=14; p++){
         printf("%s| %10s\t | %p |\n%s", KBLU,functs[p], functs[p],KNRM);
    }
    printf("-----------------------------------\n");
	for(int i =0;i<sizeof(Prog[MAXPROG]);i++){
		printf("%sInstruction [%p] installée en [%p]\n%s",KBLU,Prog[i],&Prog[i],KNRM);
		
	}
	printf("%s-----------------------------------\n%s",KBLU,KNRM);
}

/**s
 * Affichage de la pile
 */
void printPile(void){
	printf("%sPile de données:\n%s",KBLU,KNRM);
	for(int i =0;i<sizeof(Stack[MAXSTACK]);i++){
		printf("%sData value : [%f]\n%s",KBLU,Stack[i].Value,KNRM);
	}
}