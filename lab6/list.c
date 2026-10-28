
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int LA = -1;

void error(void);
int yylex(void);
void match(int c);
void D(void), N(void), C(void), L(void);

void error(void) {
    fprintf(stderr, "ERROR: Syntax error\n");
    exit(-1);
}

int yylex(void) {
    int c;
    do {
        c = getchar();
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return EOF;
    }

    if (isalnum((unsigned char)c)) {
        int next = getchar();

        if (next != EOF) {
            if (isalnum((unsigned char)next)) {
                error();
            }
            if (ungetc(next, stdin) == EOF) {
                error();
            }
        }
    }

    return c;
}

void match(int c) {
    if (LA != c) {
        error();
    }
    LA = yylex();
}

// <data> ::= <nat> | <char> | <list>
void D(void) {
    if (LA != EOF && isdigit((unsigned char)LA)) {
        N();
    } else if (LA != EOF && isalpha((unsigned char)LA)) {
        C();
    } else if (LA == '(') {
        L();
    } else {
        error();
    }
}

// <nat> ::= [0-9]
void N(void) {
    if (LA == EOF || !isdigit((unsigned char)LA)) {
        error();
    }

    putchar(LA);
    match(LA);
}

// <char> ::= [a-zA-Z]
void C(void) {
    if (LA == EOF || !isalpha((unsigned char)LA)) {
        error();
    }

    putchar(LA);
    match(LA);
}

// <list> ::= '(' { <data> } ')'
void L(void) {
    match('(');

    size_t count = 0;

    while (LA != ')') {
        if (LA == EOF) {
            error();
        }

        putchar('(');
        D();
        printf(" . ");
        ++count;
    }

    match(')');

    printf("NIL");

    while (count > 0) {
        putchar(')');
        --count;
    }
}

int main(void) {
    LA = yylex();

    while (LA != EOF) {
        D();
        putchar('\n');
    }

    return 0;
}
