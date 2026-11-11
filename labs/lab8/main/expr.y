%{
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>    
int yylex();
int yyerror(char *s);
%}
%union {
    char *sval;
    int   ival;
}
%token <ival> NUMBER
%token <sval> STRING
%type  <ival> iExp
%type  <sval> sExp
%type  <ival> iTerm
%type  <sval> sTerm
%type  <ival> iFact
%%
Exp   : iExp            { printf("%d\n", $1); }
      | sExp            { printf("\"%s\"\n", $1); free($1); }
      ;
iExp  : iExp '+' iTerm  { $$ = $1 + $3; }
      | iExp '-' iTerm  { $$ = $1 - $3; }
      | iTerm           { $$ = $1; }
      ;
iTerm : iTerm '*' iFact { $$ = $1 * $3; }
      | iTerm '/' iFact { if ($3 == 0) { yyerror("Division by zero"); } else { $$ = $1 / $3; } }
      | iFact           { $$ = $1; }
      ;
iFact : '(' iExp ')'    { $$ = $2; }
      | NUMBER          { $$ = $1; }
      ;
sExp  : sExp '+' sTerm {
           size_t len1 = strlen($1);
           size_t len2 = strlen($3);

           char *result = malloc(len1 + len2 + 1);
           if (result == NULL) {
               perror("malloc");
               exit(EXIT_FAILURE);
           }

           memcpy(result, $1, len1);
           memcpy(result + len1, $3, len2 + 1);

           free($1);
           free($3);

           $$ = result;
       }
      | sTerm { $$ = $1; }
      ;
sTerm : '(' sExp ')'    { $$ = $2; }
      | STRING          { $$ = $1; }
      ;
%%
int yyerror(char *s) 
{
    printf("%s\n", s);
    exit(-1);
}
