all: main

main: y.tab.c lex.yy.c main.c data.c env.c eval.c data.h env.h eval.h
	gcc -o main y.tab.c lex.yy.c main.c data.c env.c eval.c

lex.yy.c: token.l y.tab.h data.h env.h eval.h
	flex token.l

y.tab.c: parse.y data.h env.h eval.h
	bison -y -d parse.y

y.tab.h: parse.y data.h env.h eval.h
	bison -y -d parse.y

clean:
	rm -f main y.tab.* lex.yy.* *.zip

zip: Makefile main.c token.l parse.y data.c env.c eval.c data.h env.h eval.h
	zip env.zip Makefile main.c token.l parse.y data.c env.c eval.c data.h env.h eval.h
