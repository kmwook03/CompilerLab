#include <stdio.h>

void S(), A(), B(), C();

void S() { putchar('a'); B(); }
void A() { static int n = 0;
	if (n == 0) {
		putchar('a'); B();
	} else {
		putchar('a'); C();
	}
}
void B() { C(); }
void C() { putchar('b'); }

int main() {
	S();
	return 0;
}

