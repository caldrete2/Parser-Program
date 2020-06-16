#ifndef PROG_INC
#define PROG_INC
#include <stdio.h>
#include "stmt.h"

// a program is a statement followed by a program
typedef struct prog {
   STMT *stmt;
   struct prog *prog;
} PROG;

PROG *prog_create(STMT *stmt, PROG *prog);
void prog_print(PROG *prog);

#endif 
