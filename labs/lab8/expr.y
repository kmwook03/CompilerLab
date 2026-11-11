%{
#include <stdio.h>
#include <ctype.h>
int yyerror(const char *msg), yylex();
%}
%token NUM
%%
Line  : Exp          { printf(" = %d\n", $1); }
      ;
Exp   : Exp '+' Term { $$ = $1 + $3; }
      | Term         { $$ = $1; }
      ;
Term  : NUM          { $$ = $1;}
%%
int main() 
{ 
    yyparse(); 
    return 0; 
}
int yyerror(const char *msg) 
{ 
    puts("No"); 
    return -1;
}
int yylex() 
{
    int c = getchar();
    return (c == '\n') ? 0 : isdigit(c) ? yylval = c-'0', NUM : c;
}