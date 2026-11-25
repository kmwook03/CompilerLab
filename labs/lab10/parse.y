%{
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "data.h"
#include "env.h"
#include "eval.h"

int yylex();
int yyerror(char *s);
int evalprint(Data *exp, Data *env);

Data *Root=NULL;
Data *Env=NULL;
%}
%union {
    int ival;
    char *sval;
    Data *pval;
}
%token <ival> NUM
%token <sval> VAR SYM
%type <pval> Line Expr Atom List Exprs
%%
Prog  : { Env = mkenv(mknil()); } Lines
      ;
Lines :
      | Line { evalprint($1, Env); } Lines
      ;
Line  : Expr '\n' { $$ = $1; }
      ;
Expr  : Atom { $$ = $1; }
      | List { $$ = $1; }
      ;
Atom  : NUM { $$ = mknat($1); }
      | VAR { $$ = mksym($1); }
      | SYM { $$ = mksym($1); }
      ;
List  : '(' Exprs ')' { $$ = $2; }
      ;
Exprs : { $$ = mknil(); }
      | Expr Exprs { $$ = mkduo($1, $2); }
      ;
%%
int evalprint(Data *exp, Data *env) 
{
    Data *res=eval(exp, env);
    if (res == NULL)
        puts("_UNDEFINED_");
    else
        prdata(res), puts("");
    return 0;
}
int yyerror(char *s) 
{
    printf("%s\n", s);
}
