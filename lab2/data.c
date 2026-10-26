#include <stdio.h>
#include <ctype.h>

typedef enum _Tag { TINT, TCHR } Tag;
typedef int                      Int;
typedef char                     Chr;
typedef struct _Data {
	Tag tag;
	union {
		Int nv;
		Chr cv;
	};
} Data;

int main() {
	Data d[100];
	int i = 0, ch;
	int is_digit = 0;
	int sign = 1;
	int minus_appear = 0;
	Int val;
	
	while ((ch = getchar()) !=  EOF) {
		if (isdigit((unsigned char)ch)) {
			if (!is_digit) {
				is_digit = 1;
				val = 0;
				if (minus_appear) sign = -1;
				minus_appear = 0;
			}
			val = val * 10 + (ch - '0');
			continue;
		}

		if (is_digit) {
			if (i > 99) return 1;
			d[i].tag = TINT;
			d[i].nv  = sign * val;
			i++;

			val = 0;
			sign = 1;
			is_digit = 0;
		}

		if (minus_appear) {
			if (i > 99) return 1;
			
			d[i].tag = TCHR;
			d[i].cv  = '-';
			i++;

			minus_appear = 0;
		}

		if (ch == '-') {
			minus_appear = 1;
			continue;
		}

		if (isspace((unsigned char)ch)) {
			continue;
		}

		if (i > 99) return 1;

		d[i].tag = TCHR;
		d[i].cv = (char) ch;
		i++;
	}

	if (is_digit) {
		if (i > 99) return 1;
		d[i].tag = TINT;
		d[i].nv  = sign * val;
		i++;
	}

	if (minus_appear) {
		if (i > 99) return 1;
		d[i].tag = TCHR;
		d[i].cv  = '-';
		i++;
	}

	for (int j = 0; j < i; j++) {
		switch (d[j].tag) {
			case TINT:
				printf("(TINT, %d)\n", d[j].nv); break;
			case TCHR:
				printf("(TCHR, %c)\n", d[j].cv); break;
			default:
				fputs("Error: unknwon data type\n", stderr); break;
		}
	}

	return 0;
}

