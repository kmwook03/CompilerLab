%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
%}
digit   [0-9]
alpha   [a-zA-Z]
%%
{digit}+          { yylval.ival = atoi(yytext); return NUMBER; }
\"[^\"\r\n]+\" {
    size_t len = yyleng - 2;

    char *str = malloc(len + 1);
    if (str == NULL) exit(EXIT_FAILURE);

    memcpy(str, yytext + 1, len);
    str[len] = '\0';

    yylval.sval = str;
    return STRING;
}
[ \t\r]           {}
\n                { return 0; }
"+"               { return '+'; }
"-"               { return '-'; }
"*"               { return '*'; }
"/"               { return '/'; }
"("               { return '('; }
")"               { return ')'; }
. {
    fprintf(stderr, "'%c' is illegal\n", yytext[0]);
    exit(EXIT_FAILURE);
}
%%
int yywrap() { return 1; }