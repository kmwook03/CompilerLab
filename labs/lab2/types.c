#include <stdio.h>

typedef int  A;
typedef char B;

typedef union  _U { A a; B b; } U;
typedef struct _P { A a; B b; } P;

int main() {
	U x;
	P y;
	x.a = 2;
	x.b = 'A';
	y.b = 'C';
	printf("%d, '%c'\n", x.a, y.b);
	return 0;
}

