#include <string.h>
#include "data.h"
#include "env.h"
#include "eval.h"

Data *eval(Data *exp, Data *env)
{
    if (issymbol(exp)) {
        return envget(env, exp);
    } else if (isatom(exp) || isnil(exp)) {
        return exp;
    } else if (iskeyword(fst(exp))) {
        return evalkw(fst(exp), snd(exp), env);
    } else {
        return NULL;  
    }
}

Data *evalkw(Data *keyword, Data *args, Data *env)
{
    if (strcmp(keyword->sv, "quote") == 0) {
        return fst(args);  
    } else { 
        Data *value = eval(fst(snd(args)), env);
        if (value == NULL) {
            return NULL;
        }
        return envset(env, fst(args), value);
    }
}
