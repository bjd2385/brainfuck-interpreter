%{
#include "bf.h"
%}

%%
">"     return RCARROT;
"<"     return LCARROT;
"+"     return INC;
"-"     return DEC;
"["     return LBRACKET;
"]"     return RBRACKET;
","     return INPUT;
"."     return OUTPUT;

(\n|[^\>\<\+\-\]\[\,\.].*\r?\n) ;   /* Comments */

%%

int yywrap(void)
{
    return 1;
}
