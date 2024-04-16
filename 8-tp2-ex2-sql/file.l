%option noyywrap
%{
#include"y.tab.h"
%}
create (C|c)(R|r)(E|e)(A|a)(T|t)(E|e)
table (T|t)(A|a)(B|b)(L|l)(E|e)
parouv "("
parferm ")"
comma ","
type ("char"|"varchar"|"bool"|"int"|"bigint"|"smallint"|"float"|"date")
identifier [a-zA-Z]+
number [0-9]+

%%

{create} {return CREATE;}
{table} {return TABLE;}
{parouv} {return PAROUV;}
{parferm} {return PARFERM;}
{comma} {return COMMA;}
{type} {return TYPE;}
{identifier} {return IDENTIFIER;}
{number} {return NUMBER;}
[ \n\t]+
%%
