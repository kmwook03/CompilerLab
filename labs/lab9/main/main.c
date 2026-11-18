#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "y.tab.h"

int yyparse(void);
Tree* Root = NULL;

static Tree* mktree(void)
{
    Tree* t = malloc(sizeof(*t));
    if (t == NULL) exit(EXIT_FAILURE);
    return t;
}

static Data* mkdata(Tag tag)
{
    Data* d = malloc(sizeof(*d));
    if (d == NULL) exit(EXIT_FAILURE);
    d->tag = tag;
    return d;
}

Tree* mkint(unsigned int n)
{
    Tree* t = mktree();
    t->data = mkdata(TINT);
    t->data->nval = n;
    return t;
}

Tree* mkstr(Str s)
{
    Tree* t = mktree();
    t->data = mkdata(TSTR);
    t->data->sval = s;
    return t;
}

Tree* mksym(char c)
{
    Tree* t = mktree();
    t->data = mkdata(TSYM);
    t->data->symbol = c;
    return t;
}

Tree* mkpair(Tree* son, Tree* bro)
{
    Tree* t = mktree();
    t->data = NULL; 
    t->son = son;
    t->bro = bro;
    return t;
}

Tree* mknil()
{
    Tree* t = mktree();
    t->data = mkdata(TNIL);
    return t;
}

void printast(const Tree* t)
{
    if (t->data == NULL) { // start of a pair
        printf("(");
        printast(t->son); // first element
        printf(" . ");
        printast(t->bro); // second element
        printf(")"); // end of a pair
        return;
    }

    switch (t->data->tag) {
        case TINT: 
            printf("%d", t->data->nval); 
            break;
        case TSTR: 
            printf("%s", t->data->sval); 
            break;
        case TSYM: 
            printf("%c", t->data->symbol); 
            break;
        case TNIL: 
            printf("()");
            break;
    }
}

int maxdepth(const Tree* t)
{
    if (t->data != NULL) {
        return (t->data->tag == TNIL) ? 1 : 0;
    }

    const int son_depth = maxdepth(t->son) + 1;
    const int bro_depth = maxdepth(t->bro);
    return (son_depth > bro_depth) ? son_depth : bro_depth;
}

void free_tree(Tree* t)
{
    if (t == NULL) {
        return;
    }

    if (t->data == NULL) {
        free_tree(t->son);
        free_tree(t->bro);
    } else {
        if (t->data->tag == TSTR) {
            free(t->data->sval);
        }
        free(t->data);
    }
    free(t);
}

int main() 
{
    if (yyparse() != 0 || Root == NULL) {
        printf("_ERROR_\n");
        free_tree(Root);
        return 0;
    }
    printast(Root);
    printf("\n");
    printf("%d\n", maxdepth(Root));
    free_tree(Root);
    return 0;
}