%{
#include <stdlib.h>
#include "data.h"
#include "y.tab.h"
%}
digit [0-9]
alpha [a-zA-Z]
symbol [-+*/%=]
%%
{digit}+ { yylval.ival = atoi(yytext); return NUM; }
{alpha}({alpha}|{digit})* { yylval.sval = yytext; return VAR; }
{symbol} { yylval.sval = yytext; return SYM; }
"(" { return '('; }
")" { return ')'; }
[ \t] {}
\n { return '\n'; }
. { fprintf(stderr, "'%c' illegal\n", yytext[0]); exit(-1); }
%%
int yywrap() { return 1; }
