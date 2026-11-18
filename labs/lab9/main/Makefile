all: main

main: lex.yy.c y.tab.c y.tab.h main.c ast.h
	gcc lex.yy.c y.tab.c main.c -o main

lex.yy.c: token.l y.tab.h ast.h
	flex token.l

y.tab.c: ast.y ast.h
	bison -dy ast.y

y.tab.h: ast.y ast.h
	bison -dy ast.y

clean: 
	rm -f main lex.yy.* y.tab.* ast.zip

zip: Makefile main.c token.l ast.y ast.h
	zip ast.zip Makefile main.c token.l ast.y ast.h
