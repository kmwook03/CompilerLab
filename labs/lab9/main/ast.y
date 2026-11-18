%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
int yylex(void);
int yyerror(const char *s);
extern Tree* Root;
%}
%union {
    Str           sval;
    unsigned int  ival;
    Tree*         tval;
}
%token  <ival> NUM
%token  <sval> VAR SYM
%type   <tval> Expr Atom List Exprs
%start  Prg
%%
Prg     : Expr          { Root = $1;}
        ;
Expr    : Atom          { $$ = $1; }
        | List          { $$ = $1; }
        ;
Atom    : NUM           { $$ = mkint($1); }
        | VAR           { $$ = mkstr($1); }
        | SYM           { $$ = mksym($1[0]); free($1); }
        ;
List    : '(' Exprs ')' { $$ = $2; }
        ;
Exprs   : Expr Exprs    { $$ = mkpair($1, $2); }
        |               { $$ = mknil(); }
        ;
%%
int yyerror(const char *s)
{
    return 0;
}
