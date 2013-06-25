#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "aliases.h"
#include "value.h"

typedef struct _SYMBOL {
  STRING symbolName;		// symbol name, a means for referencing the symbol
  VALUE_PTR symbolValue;	// symbol value, defaults to being same as name
} SYMBOL, *SYMBOL_PTR;

#define SYMBOL_REF(s) 		(&s)


// SYMBOL functions
extern VALUE_PTR MAKE_SYMBOL(STRING);
extern VALUE_PTR SETQ(VALUE_PTR, VALUE_PTR);
extern STRING SYMBOL_NAME(VALUE_PTR);
extern VALUE_PTR SYMBOL_VALUE(VALUE_PTR);
extern void PRINT_SYMBOL(VALUE_PTR);

extern void FREE_SYMBOL(SYMBOL_PTR);

#endif	// _SYMBOL_H_
