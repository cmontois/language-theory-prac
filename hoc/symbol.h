/*********_********_*********_********_*********_********_***********_*********/
//                  G E S T I O N   DE  S Y M B O L E S
/*********_********_*********_********_*********_********_***********_*********/
#ifndef _SYMBOL_H_
#define _SYMBOL_H_
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libgen.h>
#include "color.h"
/*********_********_*********_********_*********_********_***********_*********/
//					Structure de Données SYMBOL
/*********_********_*********_********_*********_********_***********_*********/
typedef union {
    int     iValue;        // - une valeur entière si le type est VARINT
    double  fValue;        // - une valeur rèelle si le type est VARINT
    double (*func)();       // - une fonction PREDEF
} value_t;

typedef struct symbol {     // Structure symbol
    char *name;             // nom du symbole : identifiant
    short type;             // type du symbole : VARINT, VARFLO, PREDEF, UNDEF
    value_t value;
    struct symbol *next;    // pointeur sur symbole suivant
}   symbol_t,                 // définition du Type Symbol
* symbol_ptr_t;              // définition du Type Liste de Symbols

#define SYMBOL_NULL ((symbol_ptr_t) 0)
/*********_********_*********_********_*********_********_***********_*********/
//                  Prototypes de Fonctions
/*********_********_*********_********_*********_********_***********_*********/
// Insérer un nouveau symbole en tête de la liste des symboles
// résultat : pointeur sur symbole inséré
symbol_ptr_t installSymbol(char *tokenName,short tokenType,value_t tokenValue);
// Rechercher un symbole dans la liste des symboles
// résultat : pointeur sur symbole recherché ou NULL si non trouvé
symbol_ptr_t lookUpSymbol(char *tokenName);
// Définir des symboles à l'initialisation : cstes, fcts prédéfinies, mots-clés
void installDefaultSymbols(void);
// Afficher les symboles définis
void printSymbolList(void);
/*********_********_*********_********_*********_********_***********_*********/
#ifndef _HOC_Y_
#define _HOC_Y_
#include "hoc.tab.h"
#endif
#endif

