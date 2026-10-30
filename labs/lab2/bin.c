typedef int  B;
typedef char C;
typedef enum { TINT, TCHR } Tag;

typedef struct {
	Tag tag;
	union {
		B b;
		C c;
	};
} A;

int main() { return 0; }

