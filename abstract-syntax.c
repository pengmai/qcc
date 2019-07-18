#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "abstract-syntax.h"

void *checked_malloc(size_t size)
{
	void *p = malloc(size);
	if (!p)
	{
		fprintf(stderr, "\nRan out of memory!\n");
		exit(1);
	}
	return p;
}

Expr AST_Ident(char *name)
{
	Expr ident = checked_malloc(sizeof(*ident));
	ident->type = Identifier;
	ident->u.name = name;
	return ident;
}

Expr AST_BinaryExpr(BinaryOp op, Expr left, Expr right)
{
	Expr ex = checked_malloc(sizeof(*ex));
	ex->type = Binary;
	ex->u.binary.op = op;
	ex->u.binary.left = left;
	ex->u.binary.right = right;
	return ex;
}

Expr AST_UnaryExpr(UnaryOp op, Expr expr)
{
	Expr ex = checked_malloc(sizeof(*ex));
	ex->type = Unary;
	ex->u.unary.op = op;
	ex->u.unary.expr = expr;
	return ex;
}

void print_indent(FILE *stream, int indent)
{
	for (int i = 0; i < indent * 2; i++)
	{
		fprintf(stream, "  ");
	}
}

void print_expr_helper(FILE *stream, Expr expr, int indent)
{
	print_indent(stream, indent);
	switch (expr->type)
	{
		case Identifier:
			fprintf(stream, "%s\n", expr->u.name);
			break;
		case Unary:
			fprintf(stream, "(not\n");
			print_expr_helper(stream, expr->u.unary.expr, indent + 1);
			print_indent(stream, indent);
			fprintf(stream, ")\n");
			break;
		case Binary:
			fprintf(stream, "(");
			switch (expr->u.binary.op)
			{
				case And:
					fprintf(stream, "and\n");
					break;
				case Or:
					fprintf(stream, "or\n");
					break;
			}
			print_expr_helper(stream, expr->u.binary.left, indent + 1);
			print_expr_helper(stream, expr->u.binary.right, indent + 1);
			print_indent(stream, indent);
			fprintf(stream, ")\n");
			break;
	}
}

void print_expr(FILE *stream, Expr expr)
{
	print_expr_helper(stream, expr, 0);
}

void free_expr(Expr expr)
{
	switch (expr->type)
	{
		case Identifier:
			free(expr->u.name);
			break;
		case Unary:
			free_expr(expr->u.unary.expr);
			break;
		case Binary:
			free_expr(expr->u.binary.left);
			free_expr(expr->u.binary.right);
			break;
	}
	free(expr);
}
