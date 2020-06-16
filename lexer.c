#include <stdio.h>
#include <ctype.h>
#include "symbol.h"
#include "error.h"
#include "lexer.h"

#define BUFSIZE 256
#define EOS    '\0'   

char lexbuf[BUFSIZE];
int  lineno = 1;
int  tokenval = NONE;

// lexical analyzer
// - tokens have an integer type plus a "token attribute value":
//   - if a number, the type is NUM and tokenval is the value
//   - if a variable, the type is ID and tokenval is an index
//     into the symbol table
//   - if end-of-file, the type is DONE
//   - if 'BEGIN' or 'END' operator, the type is BEGIN or END
//   - if a single character arithmetic operator, the type is the character
//     value of the operator

void lexer_init() {
   // initialize symbol table, if necessary
   ;
}

// return integer value of most recent token (only if type is NUM)
int lexer_num_val() {
   return tokenval;
}

// return string value of most recent token (only if type is ID)
char *lexer_id_val() {
   return tok_str(tokenval);
}

// return current line number
int lexer_lineno() {
   return lineno;
}

// return the token type as an integer
// (the token attribute value is stored in global variable tokenval)
int lexan() {
   int t;
   while (1) {
      t = getchar();
      if (t == ' ' || t == '\t')
	 // skip over blanks and tabs
	 ;    
      else if (t == '\n')
	 lineno++;
      else if (isdigit(t)) {  
	 // the token is a number
	 ungetc(t, stdin);
	 scanf("%d", &tokenval);
	 return NUM;
      } else if (t == '$') {
	 // field $i (i an integer or a variable)
	 int p, b = 0;
	 lexbuf[b] = t;
	 b++; 
	 t = getchar();
	 while (isdigit(t)) {
	    lexbuf[b] = t;
	    t = getchar();
	    b++;
	    if (b >= BUFSIZE) 
	       error("compiler error");
	 }
	 lexbuf[b] = EOS;
	 if (t != EOF)
	    ungetc(t, stdin);

	 // insert the symbol into the symbol table if necessary
	 p = lookup(lexbuf);
	 if (p == 0) {
	    p = insert(lexbuf, ID);
	 }
	 tokenval = p;
	 return token(p);
      } else if (isalpha(t)) {
	 // regular variable
	 int p, b = 0;
	 while (isalnum(t)) {
	    // t is alphanumeric
	    lexbuf[b] = t;
	    t = getchar();
	    b++;
	    if (b >= BUFSIZE) 
	       error("compiler error");
	 }
	 lexbuf[b] = EOS;
	 if (t != EOF)
	    ungetc(t, stdin);

	 // insert the symbol into the symbol table if necessary
	 p = lookup(lexbuf);
	 if (p == 0) {
	    p = insert(lexbuf, ID);
	 }
	 tokenval = p;
	 return token(p);
      } else if (t == EOF) {
	 return DONE;
      } else {
	 tokenval = NONE;
	 return t;
      }
   }
} 
 
