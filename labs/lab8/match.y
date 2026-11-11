%{
#include <stdio.h>
#include <ctype.h>

#define max(x,y)	((x) > (y) ? (x) : (y))
int yyerror(const char *msg), yylex();
%}
%%
Line  : S           { printf("max. depth: %d\n", $1); }
      ;
S     : '(' S ')' S { $$ = max($2+1, $4); }
      |             { $$ = 0; }
      ;
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
    return (c == '\n') ? 0 : c;
}
