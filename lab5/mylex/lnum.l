%{
#include <stdio.h>
#include <string.h>

int lineNum = 1;
void star(int n);
%}
line	^.*\n
num		[0-9]+
%%
{num}	{ star(strlen(yytext)); }
.		{ printf("%s", yytext); }
%%
int main() {
	yylex();
	return 0;
}
int yywrap() { 
	return 1; 
}
void star(int n) {
	for (int i = 0; i < n; i++) {
		putchar('*');
	}
}
