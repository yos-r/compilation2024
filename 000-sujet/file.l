%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
%}
sql "sql"
id [a-zA-Z]([a-zA-Z]|[0-9])*
parouv "("
parferm ")"
%%
{parouv} {return PAROUV;}
{parferm} {return PARFERM;}
{sql} {return SQL;}
{id} {return ID;}
[$] {return FIN;}
[\t \n]
%%