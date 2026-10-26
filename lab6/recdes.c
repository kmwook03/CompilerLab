#include <stdio.h>
#include <stdlib.h>

int LA = -1;

int  yylex();
void match(int t);
void A(), L(), S();

// A -> eof | L A
void A()
{
	if (LA == EOF) { exit(0); }
	else { L(); A(); }
}

// L -> S '\n'
void L()
{
	S(); match('\n');
}

// S -> '(' S ')' S | 
void S()
{
	if (LA == '(') {
		match('('); S(); match(')'); S();
	} else {
		;
	}
}

int yylex() 
{
	return getchar();
}

void match(int c) 
{
	if (LA == c) {
		LA = yylex();
	} else {
		fprintf(stderr, "ERROR: Syntax error\n");
		exit(-1);
	}
}

int main() 
{
	LA = yylex();
	A();
	return 0;
}

