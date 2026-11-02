%{
	#include <stdio.h>
	#include <ctype.h>
	int yylex();
	void yyerror(const char *);
%}
%token NUM
%%
Exp : Exp '+' Term { puts("E -> E + T"); }
	| Exp '-' Term { puts("E -> E - T"); }
	| Term		   { puts("E -> T"); }
	;
Term: NUM		   { puts("T -> num"); }
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

int yylex()
{
	char c = getchar();
	return (c == '\n') ? 0 : isdigit(c) ? NUM : c;
}

