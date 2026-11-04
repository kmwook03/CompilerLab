%{
	#include <stdio.h>
	#include <ctype.h>
	extern int yylex();
	void yyerror(const char *);
%}
%token NUMBER
%token ID
%%
Exp   : Exp '+' Term      { puts("E -> E + T"); }
	  | Exp '-' Term      { puts("E -> E - T"); }
	  | Term		      { puts("E -> T"); }
	  ;
Term  : Term '*' Factor   { puts("T -> T * F"); }
	  | Term '/' Factor   { puts("T -> T / F"); }
      | Factor            { puts("T -> F"); }
      ;
Factor: NUMBER            { puts("F -> n"); }
      | ID                { puts("F -> i"); }
      ;
%%
int main() 
{ 
	yyparse(); return 0; 
}

void yyerror(const char *msg)
{
	fputs(msg, stderr);
}

