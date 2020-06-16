#include <stdlib.h>
#include "prog.h"
#include "parser.h"
#include "lexer.h"

 void main(int argc, char *argv[]) {

   // for debugging, turn off buffering on stdout
   setvbuf(stdout, NULL, _IONBF, 0);

   // parse program
   lexer_init();
   PROG *prog = parse();

   // pretty-print program
   prog_print(prog);

   exit(EXIT_SUCCESS);
}
