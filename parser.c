#include "lexer.h"
#include "error.h"
#include "expr.h"
#include "stmt.h"
#include "prog.h"

//
// a predictive parser for a super-minimal programming language
//
// refer to the BNF  

// types of functions used below
void match();
PROG *parse(), *prog();
STMT *create_stmt();
EXPR *create_expr(), *expr_fcall();

int lookahead;    // most recent token

// check that current token is t, and read next token
void match(int t) { 
    if (lookahead == t)
	lookahead = lexan();
    else error("syntax error");
} 

// parse a program
PROG *parse() {
   PROG *p;
   lookahead = lexan();
   p = prog();
   match(DONE);
   return p;
}

// one or more statements
PROG *prog() {  
   PROG *prog = NULL;
   STMT *stmt;

	do{
	  stmt = create_stmt();
      match(';');
      prog = prog_create(stmt, prog);
   } while(lookahead!= DONE);
   return prog;
}

EXPR *expr_fcall(char *id) {
	EXPR *arg;

	if(lookahead == ID){
		arg = expr_create_fcall(id, expr_create_var(lexer_id_val()));
		match(ID);
	} else if(lookahead == NUM) {
		int n = lexer_num_val();
		if(n >= 0) {
			arg = expr_create_fcall(id, expr_create_num(n));
		}
		match(NUM);
	}
	match(')');
	return arg;
}

EXPR* create_expr() {
	EXPR *expr;
	char *id_val;

	if(lookahead == ID) {
		id_val = lexer_id_val();
		match(ID);
		if(lookahead == '(') {
			match('(');
			expr = expr_fcall(id_val);
		} else {
			expr = expr_create_var(id_val);
		}
	} else if(lookahead == NUM) {
		expr = expr_create_num(lexer_num_val());
		match(NUM);
	}

	return expr;
}

STMT* create_stmt() {
	STMT *s;
	char *var;

	if(lookahead == ID) {
		var = lexer_id_val();
		match(ID);
		if(lookahead == '(') {
			match('(');
			s = stmt_create_call(var, create_expr());
			match(')');				
		} else if(lookahead == '=') {
			match('=');
			s = stmt_create_assign(var, create_expr());
		} else { error ("syntax error"); }
	}

	return s;
}

