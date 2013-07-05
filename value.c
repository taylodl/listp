#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "value.h"
#include "symbol.h"
#include "cons.h"

#define DISCRIMINANT_NIL	(0x01U)
#define DISCRIMINANT_INTEGER	(0x02U)
#define DISCRIMINANT_REAL	(0x04U)
#define DISCRIMINANT_CHARACTER	(0x08U)
#define DISCRIMINANT_STRING	(0x10U)
#define DISCRIMINANT_CONS	(0x20U)
#define DISCRIMINANT_SYMBOL	(0x40U)


/*
  Create NIL VALUE
*/
VALUE_PTR MAKE_NIL_VALUE() {
  VALUE_PTR v = (VALUE_PTR)malloc(sizeof(VALUE));
  v->discriminant = DISCRIMINANT_NIL;
  return v;
}


/*
  Create new VALUE of type INTEGER
*/
VALUE_PTR MAKE_INTEGER_VALUE(long value) {
  VALUE_PTR v = (VALUE_PTR)malloc(sizeof(VALUE));
  v->value.integer = value;
  v->discriminant = DISCRIMINANT_INTEGER;
  return v;
}


/*
  Create new VALUE of type REAL
*/
VALUE_PTR MAKE_REAL_VALUE(double value) {
  VALUE_PTR v = (VALUE_PTR)malloc(sizeof(VALUE));
  v->value.real = value;
  v->discriminant = DISCRIMINANT_REAL;
  return v;
}


/*
  Create a new VALUE of type CHARACTER
*/
VALUE_PTR MAKE_CHARACTER_VALUE(char value) {
  VALUE_PTR v = (VALUE_PTR)malloc(sizeof(VALUE));
  v->value.character = value;
  v->discriminant = DISCRIMINANT_CHARACTER;
  return v;
}


/*
  Create a new VALUE of type STRING
*/
VALUE_PTR MAKE_STRING_VALUE(STRING value) {
  VALUE_PTR v = (VALUE_PTR)malloc(sizeof(VALUE));
  v->value.string = (STRING)malloc(strlen(value) + sizeof(CHAR));
  strcpy(v->value.string, value);
  v->discriminant = DISCRIMINANT_STRING;
  return v;
}


/*
  Create a new VALUE of type CONS
*/
VALUE_PTR MAKE_CONS_VALUE(void* value) {
  VALUE_PTR v = (VALUE_PTR)malloc(sizeof(VALUE));
  v->value.cons = value;
  v->discriminant = DISCRIMINANT_CONS;
  return v;
}


/*
  Create a new VALUE of type SYMBOL
*/
VALUE_PTR MAKE_SYMBOL_VALUE(void* value) {
  VALUE_PTR v = (VALUE_PTR)malloc(sizeof(VALUE));
  v->value.symbol = value;
  v->discriminant = DISCRIMINANT_SYMBOL;
  return v;
}


/*
  Free VALUE, reclaiming memory
*/
void FREE_VALUE(VALUE_PTR v) {
  if (IS_VALUE_STRING(v)) {
    free(v->value.string);
  } else if (IS_VALUE_CONS(v)) {
    FREE_CONS(v->value.cons);
  } else if (IS_VALUE_SYMBOL(v)) {
    FREE_SYMBOL(v->value.symbol);
  }
  free(v);
}


/*
  Print VALUE, according to type 
*/
void PRINT_VALUE(VALUE_PTR v) {
  if (IS_VALUE_NIL(v)) {
    printf("NIL ");
  } else if  (IS_VALUE_INTEGER(v)) {
    printf("%ld ", v->value.integer);
  } else if (IS_VALUE_REAL(v)) {
    printf("%lf ", v->value.real);
  } else if (IS_VALUE_CHARACTER(v)) {
    printf("'%c' ", v->value.character);
  } else if (IS_VALUE_STRING(v)) {
    printf("\"%s\" ", v->value.string);
  } else if (IS_VALUE_CONS(v)) {
    PRINT_CONS(v);
  } else if (IS_VALUE_SYMBOL(v)) {
    PRINT_SYMBOL(v);
  } else {
    printf(" ");
  }
}


/*
  Get INTEGER value
*/
long GET_INTEGER_VALUE(VALUE_PTR v) {
  return v->value.integer;
}


/*
  Get REAL value
*/
double GET_REAL_VALUE(VALUE_PTR v) {
  return v->value.real;
}


/*
  Get CHARACTER value
*/
char GET_CHARACTER_VALUE(VALUE_PTR v) {
  return v->value.character;
}


/*
  Get STRING value
*/
STRING GET_STRING_VALUE(VALUE_PTR v) {
  return v->value.string;
}


/*
  Get CONS value
*/
void* GET_CONS_VALUE(VALUE_PTR v) {
  return v->value.cons;
}


/*
  Get SYMBOL value
*/
void* GET_SYMBOL_VALUE(VALUE_PTR v) {
  return v->value.symbol;
}


/*
  Is value of type NIL?
*/
BOOL IS_VALUE_NIL(VALUE_PTR v) {
  return v->discriminant & DISCRIMINANT_NIL;
}


/*
  Is value of type INTEGER?
*/
BOOL IS_VALUE_INTEGER(VALUE_PTR v) {
  return v->discriminant & DISCRIMINANT_INTEGER;
}


/*
  Is value of type REAL?
*/
BOOL IS_VALUE_REAL(VALUE_PTR v) {
  return v->discriminant & DISCRIMINANT_REAL;
}


/*
  Is value of type CHARACTER?
*/
BOOL IS_VALUE_CHARACTER(VALUE_PTR v) {
  return v->discriminant & DISCRIMINANT_CHARACTER;
}


/*
  Is value of type STRING?
*/
BOOL IS_VALUE_STRING(VALUE_PTR v) {
  return v->discriminant & DISCRIMINANT_STRING;
}


/*
  Is value of type CONS?
*/
BOOL IS_VALUE_CONS(VALUE_PTR v) {
  return v->discriminant & DISCRIMINANT_CONS;
}


/*
  Is value of type SYMBOL?
*/
BOOL IS_VALUE_SYMBOL(VALUE_PTR v) {
  return v->discriminant & DISCRIMINANT_SYMBOL;
}



int main(int argc, STRING argv[]) {
  VALUE_PTR v;

  // Integer
  long integer_value = 42;
  v = MAKE_INTEGER_VALUE(integer_value);
  PRINT_VALUE(v); printf("\n");
  assert(GET_INTEGER_VALUE(v) == integer_value);
  assert(IS_VALUE_INTEGER(v));

  // Real
  double real_value = 3.14159265358979;
  v = MAKE_REAL_VALUE(real_value);
  PRINT_VALUE(v); printf("\n");
  assert(GET_REAL_VALUE(v) == real_value);
  assert(IS_VALUE_REAL(v));

  // Character
  char character_value = 'A';
  v = MAKE_CHARACTER_VALUE(character_value);
  PRINT_VALUE(v); printf("\n");
  assert(GET_CHARACTER_VALUE(v) == character_value);
  assert(IS_VALUE_CHARACTER(v));

  // String
  STRING string_value = "The quick brown fox jumps over the lazy dog";
  v = MAKE_STRING_VALUE(string_value);
  PRINT_VALUE(v); printf("\n");
  assert(0 == strcmp(GET_STRING_VALUE(v), string_value));
  assert(IS_VALUE_STRING(v));

  // SYMBOL
  v = MAKE_SYMBOL("A");
  PRINT_VALUE(v); printf("\n");
  assert(IS_VALUE_SYMBOL(v));

  // CONS
  // (first)
  PRINT_VALUE(CONS(MAKE_SYMBOL("first"), MAKE_NIL_VALUE()));
  printf("\n");

  // (1 2 3)
  VALUE_PTR list = CONS(MAKE_SYMBOL("1"), CONS(MAKE_SYMBOL("2"), CONS(MAKE_SYMBOL("3"), MAKE_NIL_VALUE())));
  PRINT_VALUE(list);
  printf("\n");

  // (2 3)
  PRINT_VALUE(CDR(list));
  printf("\n");

  // (3)
  PRINT_VALUE(CDR(CDR(list)));
  printf("\n");

  // NIL
  PRINT_VALUE(CDR(CDR(CDR(list))));
  printf("\n");

  // 1
  PRINT_VALUE(CAR(list));
  printf("\n");

  // 2
  PRINT_VALUE(CAR(CDR(list)));
  printf("\n");

  // 3
  PRINT_VALUE(CAR(CDR(CDR(list))));
  printf("\n");

  // (NIL)
  PRINT_VALUE(CONS(MAKE_NIL_VALUE(), MAKE_NIL_VALUE()));
  printf("\n");

  // ((1))
  PRINT_VALUE(CONS(CONS(MAKE_SYMBOL("1"), MAKE_NIL_VALUE()), MAKE_NIL_VALUE()));
  printf("\n");

  // (((1)))
  PRINT_VALUE(CONS(CONS(CONS(MAKE_SYMBOL("1"), MAKE_NIL_VALUE()), MAKE_NIL_VALUE()), MAKE_NIL_VALUE()));
  printf("\n");

  // (1 (2 (3)))
  VALUE_PTR embeddedList = CONS(MAKE_SYMBOL("1"), CONS(CONS(MAKE_SYMBOL("2"), CONS(CONS(MAKE_SYMBOL("3"), MAKE_NIL_VALUE()), MAKE_NIL_VALUE())), MAKE_NIL_VALUE()));
  PRINT_VALUE(embeddedList);
  printf("\n");

  // (2 (3))
  PRINT_VALUE(CAR(CDR(embeddedList)));
  printf("\n");
  
  // (3)
  PRINT_VALUE(CAR(CDR(CAR(CDR(embeddedList)))));
  printf("\n");
  
}
