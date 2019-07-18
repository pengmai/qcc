#include <stdio.h>
#include "codegen.h"
#include "abstract-syntax.h"

/* Schema-dependent constants */
char TABLE[] = "drinks";
char ID_COLUMN[] = "drink_id";
char TAGS[] = "tags";
char TAGMAP[] = "tagmap";

void generate_sql_helper(FILE *stream, Expr expr)
{
	switch (expr->type)
	{
		case Identifier:
			fprintf(stream,
					"SELECT DISTINCT m.id FROM %s m "
					"JOIN %s tm ON m.id = tm.%s "
					"JOIN %s t ON t.id = tm.tag_id "
					"WHERE t.name = '%s'",
					TABLE, TAGMAP, ID_COLUMN, TAGS, expr->u.name);
			break;
		case Unary:
			fprintf(stream, "SELECT id FROM %s WHERE id NOT IN (", TABLE);
			generate_sql_helper(stream, expr->u.unary.expr);
			fprintf(stream, ")");
			break;
		case Binary:
			fprintf(stream, "SELECT id FROM %s WHERE id IN (", TABLE);
			generate_sql_helper(stream, expr->u.binary.left);
			fprintf(stream,
					") %s id IN (",
					expr->u.binary.op == And ? "AND" : "OR");
			generate_sql_helper(stream, expr->u.binary.right);
			fprintf(stream, ")");
			break;
	}
}

void generate_sql(FILE *stream, Expr expr)
{
	// Global initialization.
	fprintf(stream, "SELECT id, name FROM %s WHERE id IN (", TABLE);
	generate_sql_helper(stream, expr);
	fprintf(stream, ");\n");
}
