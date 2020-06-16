#ifndef LEXER_INC
#define LEXER_INC

// token type values
#define NONE    -1
#define NUM    256
#define ID     260
#define DONE   261 

// lexer methods
int  lexan();
void lexer_init();
int  lexer_num_val();
char *lexer_id_val();
int  lexer_lineno();

#endif
