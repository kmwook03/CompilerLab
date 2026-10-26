#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int LA = -1;

int  yylex();
void match(int t);
void E(), E1(), T(), T1(), F();

// E -> T E1
void E() { T(); E1(); }

// E1 -> | + T E1
void E1() 
{
	if (LA == '+') { match('+'); T(); E1(); }
	else {}
}

// T -> F T1
void T() { F(); T1(); }

// T1 -> | * F T1
void T1()
{
	if (LA == '*') { match('*'); F(); T1(); }
	else {}
}

// F -> ( E ) | num
void F()
{
	if (LA == '(') { match('('); E(); match(')'); }
	else if (isdigit(LA)) { LA = yylex(); }
	else { 
		fprintf(stderr, "ERROR: a digit is expected instead of '%c'\n", LA);
		exit(-2);
	}
}

int yylex()
{
	return getchar();
}

void match(int c)
{
	if (LA == c) { LA = yylex(); }
	else {
		fprintf(stderr, "ERROR: Syntax error\n");
		exit(-1);
	}
}

int main()
{
	LA = yylex();
	E();
	return 0;
}
