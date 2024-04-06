%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
%}
routerconfig "config-router"
network "network"
hashtag "#"
area "area"
parouv "("
parferm ")"
point "."
nb [2][0-5][0-9]|[1][0-9][0-9]|[1-9][0-9]|[0-9]
id [a-zA-Z]([a-zA-Z]|[0-9])*
%%
{routerconfig} {return CONFIGROUTER;}
{hashtag} {return HASHTAG;}
{parouv} {return PAROUV;}
{parferm} {return PARFERM;}
{area} {return AREA; }
{network} {return NETWORK;}
{id} {return ID;}

{nb} {return NB;}
{point} {return POINT;}
[$] {return FIN;}
[\t \n]
%%