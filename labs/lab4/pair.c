#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum _Tag {
    TNAT,
    TCHR,
    TNIL,
    TDUO
} Tag;

typedef struct _Pair *Duo;

typedef struct _Data {
    Tag tag;

    union {
        unsigned int nv;   // natural number
        char cv;           // character
        Duo pv;            // pair
    };
} Data;

typedef struct _Pair {
    Data *d[2];
} Pair;


static void *xmalloc(size_t size)
{
    void *p = malloc(size);

    if (p == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    return p;
}

Data *mknat(unsigned int n)
{
    Data *d = xmalloc(sizeof(*d));

    d->tag = TNAT;
    d->nv = n;

    return d;
}

Data *mkchr(char c)
{
    Data *d = xmalloc(sizeof(*d));

    d->tag = TCHR;
    d->cv = c;

    return d;
}

Data *mknil(void)
{
    static Data nil = {
        .tag = TNIL,
        .pv = NULL
    };

    return &nil;
}

Data *mkduo(Data *a, Data *b)
{
    Data *d = xmalloc(sizeof(*d));
    Pair *p = xmalloc(sizeof(*p));

    p->d[0] = a;
    p->d[1] = b;

    d->tag = TDUO;
    d->pv = p;

    return d;
}

static void skip_space(const char **s)
{
    while (**s != '\0' &&
           **s != '\n' &&
           isspace((unsigned char)**s)) {
        (*s)++;
    }
}


static Data *parse_data(const char **s);


/*
 * Parse
 *
 * ()
 *
 * or
 *
 * (data . data)
 */
static Data *parse_pair(const char **s)
{
    skip_space(s);

    if (**s != '(') {
        return NULL;
    }

    (*s)++;        // consume '('

    skip_space(s);

    /*
     * ()
     *
     * Empty pair = NIL
     */
    if (**s == ')') {
        (*s)++;    // consume ')'
        return mknil();
    }


    /*
     * Parse first component.
     */
    Data *left = parse_data(s);

    if (left == NULL) {
        return NULL;
    }


    skip_space(s);

    /*
     * Pair must contain '.'
     *
     * (a . b)
     */
    if (**s != '.') {
        return NULL;
    }

    (*s)++;        // consume '.'


    /*
     * Parse second component.
     */
    Data *right = parse_data(s);

    if (right == NULL) {
        return NULL;
    }


    skip_space(s);

    /*
     * Pair must end with ')'.
     */
    if (**s != ')') {
        return NULL;
    }

    (*s)++;        // consume ')'


    return mkduo(left, right);
}

static Data *parse_data(const char **s)
{
    skip_space(s);

    char ch = **s;


    /*
     * pair
     */
    if (ch == '(') {
        return parse_pair(s);
    }

    if (isdigit((unsigned char)ch)) {
        (*s)++;

        return mknat((unsigned int)(ch - '0'));
    }


    /*
     * These characters cannot begin character data.
     */
    if (ch == '\0' ||
        ch == '\n' ||
        ch == ')' ||
        ch == '.') {

        return NULL;
    }


    /*
     * character
     */
    (*s)++;

    return mkchr(ch);
}

static void print_data(const Data *d)
{
    switch (d->tag) {

    case TNAT:
        printf("%u", d->nv);
        break;


    case TCHR:
        printf("'%c'", d->cv);
        break;


    case TNIL:
        printf("NIL");
        break;


    case TDUO:
        printf("(");

        print_data(d->pv->d[0]);

        printf(" . ");

        print_data(d->pv->d[1]);

        printf(")");
        break;
    }
}


static void free_data(Data *d)
{
    if (d == NULL)
        return;

    /*
     * mknil() returns a static object,
     * so NIL must not be freed.
     */
    if (d->tag == TNIL)
        return;


    if (d->tag == TDUO) {

        free_data(d->pv->d[0]);
        free_data(d->pv->d[1]);

        free(d->pv);
    }

    free(d);
}


int main(void)
{
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }


    const char *p = input;

    Data *root = parse_pair(&p);

    if (root == NULL) {
        fprintf(stderr, "Invalid pair data\n");
        return 1;
    }


    skip_space(&p);

    if (*p != '\n' && *p != '\0') {
        fprintf(stderr, "Unexpected input: %c\n", *p);

        free_data(root);

        return 1;
    }


    print_data(root);
    putchar('\n');


    free_data(root);

    return 0;
}
