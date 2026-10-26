%{
#include <stdio.h>
int		int_cnt = 0, id_cnt = 0;
%}
digit	[0-9]
int		[-+]?{digit}+
char	[_a-zA-Z]
ident	{char}({char}|{digit})*
space	[ \t\n]
%%
{int}	{ int_cnt++; }
{ident}	{ id_cnt++; }
{space}	{}
.		{}
%%
int main() {
	yylex();
	printf("Number of Identifier: %3d\n", id_cnt);
	printf("Number of Integer: %3d\n", int_cnt);
}

int yywrap() { 
	return 1; 
}
