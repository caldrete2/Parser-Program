#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

void error(char *m) {
   fprintf(stderr, "line %d: %s\n", lexer_lineno(), m);
   exit(1);	// unsuccessful termination
}


