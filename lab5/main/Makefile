all: main

main: lex.yy.c main.c
	gcc lex.yy.c main.c -o main

lex.yy.c: line.l
	flex line.l

clean:
	rm main lex.yy.c

zip: Makefile line.l main.c
	zip main.zip Makefile line.l main.c
