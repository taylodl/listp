#ifndef _CONS_H_
#define _CONS_H_

#include "aliases.h"
#include "value.h"

typedef struct _CONS {
  VALUE_PTR car;
  VALUE_PTR cdr;
  BOOL _isList;
} CONS_CELL, *CONS_PTR; 


#define CONS_REF(c)	(&c)


extern VALUE_PTR CONS(VALUE_PTR, VALUE_PTR);
extern VALUE_PTR CAR(VALUE_PTR);
extern VALUE_PTR CDR(VALUE_PTR);

extern void PRINT_CONS(VALUE_PTR);
extern void FREE_CONS(CONS_PTR);

#endif	// _CONS_H_
