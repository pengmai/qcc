#include <stdio.h>
#include "abstract-syntax.h"
#include "codegen.h"

extern FILE *yyin;
extern int yyparse();
extern Expr AST_root;

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s <input file>\n", argv[0]);
		return -1;
	}

	FILE *f = fopen(argv[1], "r");
	if (!f) {
		printf("Unable to open file \"%s\"\n", argv[1]);
		return -1;
	}

	yyin = f;
	if (yyparse() == 0)
	{
		generate_sql(stdout, AST_root);
		free_expr(AST_root);
	}
	else
		fprintf(stderr, "Parsing failed\n");
}
