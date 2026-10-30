%{
    #include <stdio.h>
    extern int symbNum;    
%}
char    [a-zA-Z]
word    {char}+
symb    [!?@#$%^&*()_+=|\\/<>:;\"\'`~{}\[\].,\-]|"’"|"‘"
space   [ \t\r\n]+
%%
{word}  { printf("(WORD, %s)\n", yytext);}
{symb}  { printf("(SYMB, %s)\n", yytext); symbNum++; }
{space} {}
%%
int yywrap() {
    return 1;
}
