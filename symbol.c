#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "error.h"

#define SYMMAX 100    // size of symbol table

// Operations on symbol table used for tokens
// Each symbol table entry contains the integer value
// for a token (token), plus a pointer to its string
// (lexptr).

// a symbol table entry
struct entry {	  
    char *lexptr;
    int   token;
};

// a symbol table
struct entry symtable[SYMMAX];
int lastentry = 0; 	// last used position in symbol table

// return position of entry for s
int lookup(char s[]) {
    int p;
    for (p = lastentry; p > 0; p = p -1) 
	if (strcmp(symtable[p].lexptr, s) == 0)
	    return p;
    return 0;
}

// get token string using position in symbol table
char *tok_str(int p) {
   return symtable[p].lexptr;
}

// get token value using position in symbol table
int token(int p) {
   return symtable[p].token;
}

// insert token and its string into symbol table
int insert(char s[], int tok) {
    int len;
    len = strlen(s);
    if (lastentry + 1 >= SYMMAX) 
	error("symbol table full");
    lastentry = lastentry + 1;
    symtable[lastentry].token = tok;
    symtable[lastentry].lexptr = (char *)malloc(strlen(s) + 1);
    strcpy(symtable[lastentry].lexptr, s);
    return lastentry;
}

// print symbol table
void symtable_to_string() {
  int i;
  for (i = 0; i < lastentry; i++) {
    printf("symtable[i]; token  = %d, string = %s\n", 
	   symtable[i].token, symtable[i].lexptr);
  }
}

