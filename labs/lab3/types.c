#include <stdio.h>
#include <stdlib.h>

typedef int  B;
typedef char C;
typedef enum { TINT, TCHR } Tag;

typedef union { 
	Tag tag;
	union {
		B i; C c;
	};
} A;

const char* tagstr(Tag t) {
	return (t == TINT) ? "TINT" : "TCHR";
}

A* mk_B(int i) {
	A *d = (A*)malloc(sizeof(A));
	d->tag = TINT;
	d->i = i;

	return d;
}

A* mk_C(char c) {};

int main() {
	A* d1 = mk_B(2);
	A d2 = {TCHR, .c='A'};
	A* ds[] = {d1, &d2};
	for (int i = 0; i < 2; i++) {
		printf("ds[%d].tag = %s\n", i, tagstr(ds[i]->tag));
	}

	return 0;
}

