#ifndef STMT_INC
#define STMT_INC

#include "expr.h"

// a statement
//
// A statement can be either a call or an assignment
// statement.  I use an ugly hack so that this "class"
// can capture both kinds of statements.

// valid statement types
#define CALL_TYPE 0
#define ASSIGN_TYPE 1

typedef struct stmt {
   int stmt_type;    // indicates call or assign statement
   char *id;        
   EXPR *expr;
} STMT;

STMT *stmt_create_assign(char *var, EXPR *expr);
STMT *stmt_create_call(char *fname, EXPR *expr);
void stmt_print(STMT *stmt);

#endif
