%{
#include<stdio.h>
#include<stdlib.h>
#include "abstract-syntax.h"
#include "codegen.h"

extern int yylex();
extern int yyparse();
extern FILE *yyin;

void yyerror(const char *s);
Expr AST_root;

%}

%union {
char *sval;
Expr exp;
}

%token AND OR NOT
%token <sval> STRING

%type <exp> query orexpr andexpr notexpr atom

%%

query:
	orexpr                 { AST_root = $1; }
;

orexpr:
	orexpr OR andexpr      { $$ = AST_BinaryExpr(Or, $1, $3); }
	| andexpr              { $$ = $1; }
;

andexpr:
	andexpr AND notexpr    { $$ = AST_BinaryExpr(And, $1, $3); }
	| notexpr              { $$ = $1; }
;

notexpr:
	NOT notexpr        	   { $$ = AST_UnaryExpr(Not, $2); }
	| atom           	   { $$ = $1; }
;

atom:
	STRING                 { $$ = AST_Ident($1); }
	| '(' query ')'        { $$ = $2; }
;

%%

void yyerror(const char *s) {
	printf("Parse error: %s\n", s);
	exit(-1);
}
