%{
#include <stdio.h>
#include <string.h>
%}

%%
.* { printf("%s%s", yytext, yytext); }
%%
int main() {
	yylex();
	return 0;
}

int yywrap() {
	return 1;
}
