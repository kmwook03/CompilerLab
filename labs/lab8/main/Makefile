all: main

main: lex.yy.c y.tab.c y.tab.h main.c
	gcc lex.yy.c y.tab.c main.c -o main

lex.yy.c: token.l
	flex token.l

y.tab.c: expr.y
	bison -dy expr.y

y.tab.h: expr.y
	bison -dy expr.y

clean: 
	rm main lex.yy.* y.tab.*

zip: Makefile main.c token.l expr.y
	zip main.zip Makefile main.c token.l expr.y
