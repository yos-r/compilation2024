%option noyywrap
/* SUJET SQL*/
%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
%}
id [a-zA-Z]([a-zA-Z]|[0-9])*
parouv "("
parferm ")"
%%
("SELECT"|"select") {return SELECT;}
("CREATE"|"create") {return CREATE;}
("INSERT"|"insert") {return INSERT;}
("INTO"|"into") {return INTO;}
("WHERE"|"where") {return WHERE;}
("FROM"|"from") {return FROM;}
[0-9]+ {yylval=atoi(yytext); return NB;}
("=="|"!="|"<>"|"<="|">="|"<"|">") {return COMP;}
{parferm} {return PARFERM;}
{parouv} {return PAROUV;}
{id} {return ID;}
[,|.] {return yytext[0];}
[$] {return FIN;}
[\n] return 0;

%%