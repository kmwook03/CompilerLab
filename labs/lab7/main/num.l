%{
#include <stdlib.h>
#include "y.tab.h"
%}
%%
[0-9]+    return(NUMBER);
[a-zA-Z]+ return(ID);
[ \t]     ;
\+        return('+');
\-        return('-');
\*        return('*');
\/        return('/');
\n        return(0);
.         { printf("'%c': illegal character\n", yytext[0]); exit(-1); }
%%
int yywrap() 
{
    return 1;
}
