#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

Data *mknat(Nat n)
{
    Data *data = malloc(sizeof(Data));
    data->tag = TNAT;
    data->nv = n;
    return data;
}

Data *mkchr(Chr c)
{
    Data *data = malloc(sizeof(Data));
    data->tag = TCHR;
    data->cv = c;
    return data;
}

Data *mkstr(Str s)
{
    Data *data = malloc(sizeof(Data));
    data->tag = TSTR;
    data->sv = s;
    return data;
}

Data *mksym(Str s)
{
    Data *data = malloc(sizeof(Data));
    data->tag = TSYM;
    data->sv = strdup(s);
    return data;
}

Data *mknil()
{
    Data *data = malloc(sizeof(Data));
    data->tag = TNIL;
    return data;
}

Data *mkduo(Data *a, Data *b)
{
    Pair *pair = malloc(sizeof(Pair));
    pair->d[0] = a;
    pair->d[1] = b;

    Data *data = malloc(sizeof(Data));
    data->tag = TDUO;
    data->pv = pair;
    return data;
}

Data *fst(Data *duo)
{
    return duo->pv->d[0];
}

Data *snd(Data *duo)
{
    return duo->pv->d[1];
}

Data **pfst(Data *duo)
{
    return &(duo->pv->d[0]);
}

Data **psnd(Data *duo)
{
    return &(duo->pv->d[1]);
}

int isatom(Data *d)
{
    if (d->tag == TNAT || d->tag == TCHR || d->tag == TSTR || d->tag == TSYM) {
        return 1;
    } else {
        return 0;
    }
}

int islist(Data *d)
{
    if (d->tag == TNIL || d->tag == TDUO) {
        return 1;
    } else {
        return 0;
    }
}

int isnil(Data *d)
{
    if (d->tag == TNIL) {
        return 1;
    } else {
        return 0;
    }
}

int isduo(Data *d)
{
    if (d->tag == TDUO) {
        return 1;
    } else {
        return 0;
    }
}

int issymbol(Data *d)
{
    if (d->tag == TSYM) {
        return 1;
    } else {
        return 0;
    }
}

int iskeyword(Data *d)
{
    if (issymbol(d) && (strcmp(d->sv, "quote") == 0 || strcmp(d->sv, "=") == 0)) {
        return 1;
    } else {
        return 0;
    }
}

int prast(Data *root)
{
    return prdata(root); 
}

int prdata(Data *d)
{
    if (isnil(d)) {
        return printf("()");
    } else if (isduo(d)) {
        return prduo(d);
    } else {
        return pratom(d);
    }
}

int pratom(Data *d)
{
    if (d->tag == TNAT) {
        return printf("%u", d->nv);
    } else if (d->tag == TCHR) {
        return printf("%c", d->cv);
    } else if (d->tag == TSTR) {
        return printf("\"%s\"", d->sv);
    } else if (d->tag == TSYM) {
        return printf("%s", d->sv);
    } else {
        return 0;
    }
}

int prduo(Data *d)
{
    int n = printf("(");
    n += prdata(fst(d));
    n += printf(" . ");
    n += prdata(snd(d));
    n += printf(")");
    return n;
}
