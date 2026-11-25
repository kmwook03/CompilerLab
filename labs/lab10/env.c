#include <string.h>
#include "data.h"
#include "env.h"

Data *mkenv(Data *up)
{
    Data *env = mkduo(up, mknil());
    return env;
}

Data *envget(Data *env, Data *name)
{
    while (!isnil(env)) {
        Data *b = snd(env);
        while (!isnil(b)) {
            Data *bind = fst(b);
            if (strcmp(fst(bind)->sv, name->sv) == 0) {
                return snd(bind);
            }
            b = snd(b);
        }
        env = fst(env); 
    }
    return NULL;
}

Data *envset(Data *env, Data *name, Data *value)
{
    *psnd(env) = mkduo(mkduo(name, value), snd(env));
    return env;
}
