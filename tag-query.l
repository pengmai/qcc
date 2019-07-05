%{
#include <stdio.h>
#include "abstract-syntax.h"
#include "tag-query.tab.h"
%}
%option noyywrap
%%
--.+\n         ;
[ \t\n]        ;
\(             { return '('; }
\)             { return ')'; }
"and"          { return AND; }
"or"           { return OR; }
"not"          { return NOT; }
[a-zA-Z0-9\-_]+   {
	yylval.sval = strdup(yytext);
	return STRING;
}

%%

