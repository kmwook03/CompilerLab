#include <stdio.h>

int symbNum = 0;

int yylex();

int main() {
    yylex();
    printf("%d", symbNum);
    return 0;
}
