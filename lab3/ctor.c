#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum _Tag { TINT, TCHR } Tag;
typedef struct _Data {
	Tag t;
	union {
		int  i;
		char c;
	};
} Data;

Data* make_TINT(int i) {
	Data* d = (Data *)malloc(sizeof(Data));
	d->t = TINT;
	d->i = i;
	return d;
}

Data* make_TCHR(char c) {
	Data* d = (Data *)malloc(sizeof(Data));
	d->t = TCHR;
	d->c = c;
	return d;
}

int main() {
	int i = 0, ch;
	Data* d[100];
	while ((ch = getchar()) != EOF) {
		if (isspace(ch)) continue;
		if (isdigit((unsigned char)ch)) {
			d[i] = make_TINT(ch - '0');
		} else {
			d[i] = make_TCHR((unsigned char)ch);
		}
		i++;
	}

	for (int j = i-1; j >= 0; j--) {
		if (d[j]->t == TINT) {
			int out_i = d[j]->i + 1;
			printf("(TINT, %d)\n", out_i);
		} else {
			char out_c = d[j]->c + 1;
			if (out_c > 'Z' && out_c < 'a') out_c = 'A';
			else if (out_c > 'z') out_c = 'a';
			printf("(TCHR, %c)\n", out_c);
		}
	}
	return 0;
}

