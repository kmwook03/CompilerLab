#ifndef __EVAL_H__
#define __EVAL_H__

#include "data.h"
#include "env.h"

Data *eval(Data *exp, Data *env);
Data *evalkw(Data *keyword, Data *args, Data *env);

#endif
