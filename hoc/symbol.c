#include "symbol.h"
/*********_********_*********_********_*********_********_***********_*********/
//                  G E S T I O N   DE  S Y M B O L E S
/*********_********_*********_********_*********_********_***********_*********/
// Déclaration de la Table des symboles gérée en Liste
static symbol_ptr_t symbolList = SYMBOL_NULL;
/*********_********_*********_********_*********_********_***********_*********/
// Afficher les symboles définis
void printSymbolList(void)
{
    symbol_ptr_t sp;
	
	printf("%sConstantes:\n%s",KBLU,KNRM);
	for (sp = symbolList; sp != SYMBOL_NULL; sp = sp->next)
        if (sp->type == CSTFLO) printf("%s\t%s\t= %.8g\n%s",KBLU, sp->name, sp->value.fValue,KNRM);
    printf("%sVariables Réelles:\n%s",KBLU,KNRM);
    for (sp = symbolList; sp != SYMBOL_NULL; sp = sp->next)
        if (sp->type == VARFLO) printf("%s\t%s\t= %.8g\n%s",KBLU, sp->name, sp->value.fValue,KNRM);
    printf("%sVariables Entières:\n%s",KBLU,KNRM);
    for (sp = symbolList; sp != SYMBOL_NULL; sp = sp->next)
        if (sp->type == VARINT) printf("%s\t%s\t= %8i\n%s",KBLU, sp->name, sp->value.iValue,KNRM);
    printf("%s\nNon définis :\n\t%s",KBLU,KNRM);
    for (sp = symbolList; sp != SYMBOL_NULL; sp = sp->next)
        if (sp->type == UNDEF)
            printf("%s ", sp->name);
    printf("\n");
}
/*********_********_*********_********_*********_********_***********_*********/
// Rechercher un symbole dans la liste des symboles
// résultat : pointeur sur symbole recherché ou NULL si non trouvé
symbol_ptr_t lookUpSymbol(char *tokenName)
{
    symbol_ptr_t sp;
    
    for (sp = symbolList; sp != SYMBOL_NULL; sp = sp->next)
        if (strcmp(sp->name, tokenName) == 0) return sp;
    return SYMBOL_NULL;             // token non trouvé
}
/*********_********_*********_********_*********_********_***********_*********/
// Insérer un nouveau symbole en tête de la liste des symboles
// résultat : pointeur sur symbole inséré
symbol_ptr_t installSymbol(char *tokenName,short tokenType,value_t tokenValue)
{
    symbol_ptr_t sp;
    
    sp          = (symbol_ptr_t) malloc(sizeof(symbol_t));
    sp->name    = malloc(strlen(tokenName)+1);
    strcpy(sp->name, tokenName);
    sp->type    = tokenType;
    sp->value   = tokenValue;
    sp->next    = symbolList;
    symbolList  = sp;
    return sp;
}
/*********_********_*********_********_*********_********_***********_*********/
