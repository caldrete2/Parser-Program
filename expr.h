#ifndef EXPR_INC
#define EXPR_INC

// an expression
//
// An expression can be a variable, a number, or a 
// function call.  I use a hack so that this "class"
// can capture all kinds of expressions.

// valid expression types
#define VAR_EXPR 0       
#define NUM_EXPR 1       
#define FCALL_EXPR 2     

// A C union could have been used here if storage were important
typedef struct expr {
   int expr_type;        
   char *s;              // for variable or function call
   int  i;               // for num
   struct expr *expr;    // for function call
} EXPR;

EXPR *expr_create_var(char *s);
EXPR *expr_create_num(int i);
EXPR *expr_create_fcall(char *fname, EXPR *expr);
void  expr_print(EXPR *expr);

#endif


