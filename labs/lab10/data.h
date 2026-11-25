#ifndef __DATA_H__
#define __DATA_H__
typedef enum { TNAT, TCHR, TSTR, TSYM, TNIL, TDUO } Tag;
typedef unsigned int Nat;
typedef char Chr;
typedef char *Str;
typedef struct _Pair *Duo;
typedef struct _Data {
    Tag tag;
    union {
        Nat nv;
        Chr cv;
        Duo pv;
        Str sv;
    };
} Data;
typedef struct _Pair {
    Data *d[2];
} Pair;

Data *mknat(Nat n);
Data *mkchr(Chr c);
Data *mkstr(Str s);
Data *mksym(Str s);
Data *mknil();
Data *mkduo(Data *a, Data *b);

Data *fst(Data *duo);
Data *snd(Data *duo);
Data **pfst(Data *duo);
Data **psnd(Data *duo);

int isatom(Data *);
int islist(Data *);
int isnil(Data *);
int isduo(Data *);
int issymbol(Data *);
int iskeyword(Data *);

int prast(Data *root);
int prdata(Data *d);
int pratom(Data *d);
int prduo(Data *d);

#endif
