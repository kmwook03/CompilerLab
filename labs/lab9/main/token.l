%{
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "y.tab.h"
static char* copy_token(const char* text, size_t len)
{
    char* s = malloc(len + 1);
    if (s == NULL) exit(EXIT_FAILURE);
    memcpy(s, text, len);
    s[len] = '\0';
    return s;
}
%}
digit   [0-9]
alpha   [a-zA-Z]
%%
{digit}+ { 
    yylval.ival = atoi(yytext); 
    return NUM; 
}
{alpha}({alpha}|{digit})* {
    yylval.sval = copy_token(yytext, (size_t)yyleng);
    return VAR;
}
"+"|"-"|"*"|"/"   {
    yylval.sval = copy_token(yytext, (size_t)yyleng);
    return SYM;
}
"("|")"           { return yytext[0]; }
[ \t\r\n]         {}
.                 { exit(EXIT_FAILURE); }
%%
int yywrap()
{
    return 1;
}
