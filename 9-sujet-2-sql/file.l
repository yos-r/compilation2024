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
"DECIMAL" {return DECIMAL;}
("SELECT"|"select") {return SELECT;}
("CREATE"|"create") {return CREATE;}
("INSERT"|"insert") {return INSERT;}
("INTO"|"into") {return INTO;}
("WHERE"|"where") {return WHERE;}
("FROM"|"from") {return FROM;}
("TABLE"|"table") {return TABLE;}
("INT"|"DATE") {return TYPE;}
[0-9]+ {yylval.intValue=atoi(yytext); return NB;}
("=="|"!="|"<>"|"<="|">="|"<"|">") {return COMP;}
{parferm} {return PARFERM;}
{parouv} {return PAROUV;}
{id} {yylval.stringValue = strdup(yytext); return ID;}
\-\-.* {return COMMENT;}
[;] {return POINTVIRGULE;}
[,|.] {return yytext[0];}
[$] {return FIN;}
[\n] return 0;

%%