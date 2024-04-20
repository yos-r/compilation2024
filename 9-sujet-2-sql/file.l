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
("PRIMARY KEY"|"primary key") {return PRIMARY_KEY;}
("UPDATE"|"update") {return UPDATE;}
("DELETE"|"delete") {return DELETE;}
("CREATE"|"create") {return CREATE;}
("INSERT"|"insert") {return INSERT;}
("INTO"|"into") {return INTO;}
("VALUES"|"values") {return VALUES;}
("null"|"NULL") {return NULLL;}
("WHERE"|"where") {return WHERE;}
("FROM"|"from") {return FROM;}
("TABLE"|"table") {return TABLE;}
("INT"|"VARCHAR"|"NUMERIC") {return TYPE;}
[0-9]+ {yylval.intValue=atoi(yytext); return NB;}
[0-9]+.[0-9]+ {{yylval.floatValue=atof(yytext); return NUMERIC;}}
("="|"<>"|"<="|">="|"<"|">") {return COMP;}
{parferm} {return PARFERM;}
{parouv} {return PAROUV;}
{id} {yylval.stringValue = strdup(yytext); return ID;}
\-\-.* {yylval.stringValue = strdup(yytext); return COMMENT;}
\".*\" {yylval.stringValue = strdup(yytext); return STRING;}
[;] {return POINTVIRGULE;}
[,|.] {return yytext[0];}
[$] {return FIN;}
[\n] return 0;

%%