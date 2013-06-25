#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cons.h"
#include "symbol.h"

#define CONS_IS_LIST(c) (((CONS_PTR)GET_CONS_VALUE((c)))->_isList)


/*
  Create a new CONS given both the CAR and CDR
*/
VALUE_PTR CONS(VALUE_PTR car, VALUE_PTR cdr) {
  assert(car != NULL);
  assert(cdr != NULL);

  CONS_PTR cons = (CONS_PTR) malloc(sizeof(CONS_CELL));
  cons->car = car;
  cons->cdr = cdr;

  // determine if this CONS is a LIST
  if (IS_VALUE_NIL(cdr)) {
    // if CDR is NULL, then this CONS is a LIST
    cons->_isList = TRUE;
  } else if (IS_VALUE_CONS(cdr)) {
    // appending a CONS to a LIST makes a LIST
    cons->_isList = ((CONS_PTR)GET_CONS_VALUE(cdr))->_isList;
  } else {
    // CDR is not NIL and is notCONS, this is not a LIST
    cons->_isList = FALSE;
  }
  return MAKE_CONS_VALUE(cons);
}


/*
  Return the CAR of the CONS
*/
VALUE_PTR CAR(VALUE_PTR cons) {
  assert(cons != NULL);

  if (IS_VALUE_CONS(cons)) {
    return ((CONS_PTR)GET_CONS_VALUE(cons))->car;
  } else {
    return NULL;
  }
}


/*
  Return the CDR of the CONS
*/
VALUE_PTR CDR(VALUE_PTR cons) {
  assert(cons != NULL);

  if (IS_VALUE_CONS(cons)) {
    return ((CONS_PTR)GET_CONS_VALUE(cons))->cdr;
  } else {
    return NULL;
  }
}


void _PRINT(VALUE_PTR item) {
  assert(item != NULL);

  if (IS_VALUE_SYMBOL(item)) {
    PRINT_SYMBOL(item);
  } else if (IS_VALUE_CONS(item)) {
    if (CONS_IS_LIST(item)) {
      VALUE_PTR cdr = CDR(item);
      if (IS_VALUE_CONS(CAR(item))) {
	printf("(");
	_PRINT(CAR(item));
	if (!IS_VALUE_NIL(cdr)) {
	  _PRINT(CDR(item));
	}
	printf("\b) ");
      } else {
	_PRINT(CAR(item));
	if (!IS_VALUE_NIL(cdr)) {
	  _PRINT(CDR(item));
	}
      }
    } else {
      printf("(");
      _PRINT(CAR(item));
      printf(". ");
      _PRINT(CDR(item));
      printf(" ");
    } 
  }
  else {
    PRINT_VALUE(item);
  }
}


void PRINT_CONS(VALUE_PTR cons) {
  if (CONS_IS_LIST(cons)) {
    printf("(");
    if (IS_VALUE_CONS(CAR(cons))) {
      printf("(");
      _PRINT(CAR(cons));
      printf("\b) ");
    } else {
      _PRINT(CAR(cons));
    }
    VALUE_PTR cdr = CDR(cons);
    if (!IS_VALUE_NIL(cdr)) {
      _PRINT(CDR(cons));
    }
    printf("\b) ");
  } else {
    _PRINT(cons);
  }
  printf("\b ");
}


void FREE_CONS(CONS_PTR cons) {
  if (cons->car != NULL) {
    FREE_VALUE(cons->car);
  }

  if (cons->cdr != NULL) {
    FREE_VALUE(cons->cdr);
  }
}


/* int main(int argc, STRING argv[]) { */
/*   CONS_CELL_PTR cons = CONS(MAKE_SYMBOL("first"), NULL); */
/*   PRINT(cons);			// (first) */

/*   LIST list = CONS(MAKE_SYMBOL("1"), CONS(MAKE_SYMBOL("2"), CONS(MAKE_SYMBOL("3"), NULL))); */
/*   PRINT(list);			// (1 2 3) */

/*   PRINT(CDR(list));		// (2 3) */
/*   PRINT(CDR(CDR(list)));	// (3) */
/*   PRINT(CDR(CDR(CDR(list))));	// NIL */

/*   PRINT(CAR(list));		// 1 */
/*   PRINT(CAR(CDR(list)));	// 2 */
/*   PRINT(CAR(CDR(CDR(list))));	// 3 */

/*   PRINT(CONS(NULL, NULL));	// (NIL) */

/*   PRINT(CONS(CONS(MAKE_SYMBOL("1"), NULL), NULL));	// ((1)) */
/*   PRINT(CONS(CONS(CONS(MAKE_SYMBOL("1"), NULL), NULL), NULL));	// (((1))) */

/*   LIST list2 = CONS(MAKE_SYMBOL("1"), CONS(CONS(MAKE_SYMBOL("2"), CONS(CONS(MAKE_SYMBOL("3"), NULL), NULL)), NULL)); */
/*   PRINT(list2);			// (1 (2 (3))) */
/* } */
