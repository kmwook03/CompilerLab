#ifndef __AST_H__
#define __AST_H__

typedef char* Str;

typedef enum {
    TINT,
    TSTR,
    TSYM,
    TNIL
} Tag;

typedef struct _Data {
    Tag tag;
    union {
        unsigned int nval;    // natural number
        Str          sval;    // string
        char         symbol;  // pair
    };
} Data;

typedef struct T Tree;

// if Data is Null this is a pair
struct T {
    Data* data;
    Tree* bro;
    Tree* son;
};

Tree* mkint(unsigned int n);
Tree* mkstr(Str s);
Tree* mksym(char c);
Tree* mkpair(Tree* son, Tree* bro);
Tree* mknil();

void printast(const Tree* t);
int  maxdepth(const Tree* t);
void free_tree(Tree* t);

#endif
