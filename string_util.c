#include <string.h>
#include <stdlib.h>

// return a new copy of given string s
char *str_dup(char *s) {
   char *t = (char *)malloc(strlen(s)+1);
   strcpy(t, s);
   return t;
}
