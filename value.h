#ifndef _VALUE_H
#define _VALUE_H

#include "aliases.h"

typedef struct _VALUE {
  union {
    long integer;
    double real;
    char character;
    STRING string;
    void* cons;
    void* symbol;
  } value;

  int discriminant;
} VALUE, *VALUE_PTR;

#define VALUE_REF(v) (&v)

// VALUE functions
extern VALUE_PTR MAKE_NIL_VALUE();
extern VALUE_PTR MAKE_INTEGER_VALUE(long);
extern VALUE_PTR MAKE_REAL_VALUE(double);
extern VALUE_PTR MAKE_CHARACTER_VALUE(char);
extern VALUE_PTR MAKE_STRING_VALUE(STRING);
extern VALUE_PTR MAKE_CONS_VALUE(void*);
extern VALUE_PTR MAKE_SYMBOL_VALUE(void*);
extern void FREE_VALUE(VALUE_PTR);
extern void PRINT_VALUE(VALUE_PTR);

extern long GET_INTEGER_VALUE(VALUE_PTR);
extern double GET_REAL_VALUE(VALUE_PTR);
extern char GET_CHARACTER_VALUE(VALUE_PTR);
extern STRING GET_STRING_VALUE(VALUE_PTR);
extern void* GET_CONS_VALUE(VALUE_PTR);
extern void* GET_SYMBOL_VALUE(VALUE_PTR);

extern BOOL IS_VALUE_NIL(VALUE_PTR);
extern BOOL IS_VALUE_INTEGER(VALUE_PTR);
extern BOOL IS_VALUE_REAL(VALUE_PTR);
extern BOOL IS_VALUE_CHARACTER(VALUE_PTR);
extern BOOL IS_VALUE_STRING(VALUE_PTR);
extern BOOL IS_VALUE_CONS(VALUE_PTR);
extern BOOL IS_VALUE_SYMBOL(VALUE_PTR);

#endif	// _VALUE_H
