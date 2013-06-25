#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbol.h"

/* 
   Create a new SYMBOL provided the symbolName. The symbolValue will
   be initialized to NULL. Use SETQ to set the symbolValue.
*/
VALUE_PTR  MAKE_SYMBOL(STRING symbolName) {
  assert(symbolName != NULL);

  SYMBOL_PTR symbol = (SYMBOL_PTR)malloc(sizeof(SYMBOL));
  // don't alias the symbolName argument, make a copy
  symbol->symbolName = (STRING)malloc(strlen(symbolName)+sizeof(CHAR));
  strcpy(symbol->symbolName, symbolName);
  symbol->symbolValue = NULL;
  return MAKE_SYMBOL_VALUE(symbol);
}


/*
  Return the name of the SYMBOL
*/
STRING SYMBOL_NAME(VALUE_PTR symbol) {
  if (symbol != NULL && IS_VALUE_SYMBOL(symbol)) {
    return ((SYMBOL_PTR)GET_SYMBOL_VALUE(symbol))->symbolName;
  } else {
    return NULL;
  }
}


/*
  Return the value of the SYMBOL
*/
VALUE_PTR SYMBOL_VALUE(VALUE_PTR symbol) {
  if (symbol != NULL && IS_VALUE_SYMBOL(symbol)) {
    return ((SYMBOL_PTR)GET_SYMBOL_VALUE(symbol))->symbolValue;
  } else {
    return NULL;
  }
}


/* 
   Release SYMBOL_NAME to memory
*/
void FREE_SYMBOL_NAME(SYMBOL_PTR symbol) {
  assert(symbol != NULL);

  if (symbol->symbolName != NULL) {
    free(symbol->symbolName);
    symbol->symbolName = NULL;
  }
}


/* 
   Release SYMBOL_VALUE to memory
*/
void FREE_SYMBOL_VALUE(SYMBOL_PTR symbol) {
  assert(symbol != NULL);

  if (symbol->symbolValue != NULL) {
    FREE_VALUE(symbol->symbolValue);
    symbol->symbolValue = NULL;
  }
}


/* 
   Release SYMBOL_PTR to memory, releasing all consituent members 
*/
void FREE_SYMBOL(SYMBOL_PTR symbol) {
  assert(symbol != NULL);

  FREE_SYMBOL_NAME(symbol);
  FREE_SYMBOL_VALUE(symbol);
  free(symbol);
  return;
}


/* 
   Change the value of an existing, i.e. already initialized, symbol. 
*/
VALUE_PTR SETQ(VALUE_PTR symbol, VALUE_PTR symbolValue) {
  if (symbol != NULL && IS_VALUE_SYMBOL(symbol)) {
    FREE_VALUE(symbol->value.symbol);
    ((SYMBOL_PTR)symbol->value.symbol)->symbolValue = symbolValue;
    return symbol;
  } else {
    return MAKE_NIL_VALUE();
  }
}


/*
  Print symbol name
*/
void PRINT_SYMBOL_NAME(VALUE_PTR symbol) {
  if (symbol != NULL && IS_VALUE_SYMBOL(symbol)) {
    printf("%s ", ((SYMBOL_PTR)GET_SYMBOL_VALUE(symbol))->symbolName);
  } else {
    printf("NIL ");
  }
}


/*
  Print symbol value
*/
void PRINT_SYMBOL_VALUE(VALUE_PTR symbol) {
  if (symbol != NULL && IS_VALUE_SYMBOL(symbol)) {
    PRINT_VALUE(symbol);
  } else {
    printf("NIL ");
  }
}


/*
  Print symbol, this prints the name
*/
void PRINT_SYMBOL(VALUE_PTR symbol) {
  PRINT_SYMBOL_NAME(symbol);
}
