#pragma once
#include <stdio.h>

/* Type definitions */
typedef struct Expr_ *Expr;
typedef enum { And, Or } BinaryOp;
typedef enum { Not } UnaryOp;

/* AST Nodes */
struct Expr_
{
	 enum { Identifier, Binary, Unary } type;
	 union
	 {
		 char *name;
		 struct {
			 BinaryOp op;
			 Expr left;
			 Expr right;
		 } binary;
		 struct {
			 UnaryOp op;
			 Expr expr;
		 } unary;
	 } u;
};

Expr AST_Ident(char *);
Expr AST_BinaryExpr(BinaryOp op, Expr left, Expr right);
Expr AST_UnaryExpr(UnaryOp op, Expr expr);

void print_expr(FILE *stream, Expr expr);
void free_expr(Expr expr);
