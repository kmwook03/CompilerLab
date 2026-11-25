#ifndef __ENV_H__
#define __ENV_H__

#include "data.h"

Data *mkenv(Data *up);
Data *envget(Data *env, Data *name);
Data *envset(Data *env, Data *name, Data *value);

#endif