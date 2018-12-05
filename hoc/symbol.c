#include "symbol.h"

// Déclaration de la Table des symboles gérée en Liste
static symbol_ptr_t symbolList = SYMBOL_NULL;

// Afficher les symboles définis
void printSymbolList(void)
{
    symbol_ptr_t sp;
    
    printf("Variables Réelles:\n");
    for (sp = symbolList; sp != SYMBOL_NULL; sp = sp->next)
        if (sp->type == VARFLO) printf("\t%s\t= %.8g\n", sp->name, sp->value.fValue);
    printf("Variables Entières:\n");
    for (sp = symbolList; sp != SYMBOL_NULL; sp = sp->next)
        if (sp->type == VARINT) printf("\t%s\t= %8i\n", sp->name, sp->value.iValue);
    printf("\nNon définis :\n\t");
    for (sp = symbolList; sp != SYMBOL_NULL; sp = sp->next)
        if (sp->type == UNDEF)
            printf("%s ", sp->name);
    printf("\n");
}

symbol_ptr_t lookUpSymbol(char *tokenName)
{
  symbol_ptr_t sp;
  for (sp = symbolList; sp != SYMBOL_NULL; sp = sp->next)
  if (strcmp(sp->name, tokenName) == 0) return sp;
  return SYMBOL_NULL; /* Item not found */
}

symbol_ptr_t install(char *tokenName, short tokenType, value_t tokenValue)
{
  symbol_ptr_t sp;
  sp = (symbol_ptr_t) malloc(sizeof(symbol_t));
  sp->name = malloc(strlen(tokenName)+1); strcpy(sp->name, tokenName);
  sp->type = tokenType;
  sp->value = tokenValue;
  sp->next = symbolList;
  symbolList = sp;
  return sp;
} 