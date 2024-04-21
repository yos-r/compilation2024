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
("FOREIGN KEY"|"foreign key") {return FOREIGN_KEY;}
("REFERENCES"|"references") {return REFERENCES;}

("UPDATE"|"update") {return UPDATE;}
("DELETE"|"delete") {return DELETE;}
("CREATE"|"create") {return CREATE;}
("INSERT"|"insert") {return INSERT;}
("DROP"|"drop") {return DROP;}
("INTO"|"into") {return INTO;}
("VALUES"|"values") {return VALUES;}
("null"|"NULL") {return NULLL;}
("WHERE"|"where") {return WHERE;}
("SET"|"set") {return SET;}
\* {return ALL;}
\= {return EGAL;}
\<\> {return DIFF;}
("FROM"|"from") {return FROM;}
("TABLE"|"table") {return TABLE;}
("INT"|"int") {return INT;}
("VARCHAR"|"varchar") {return VARCHAR;}
("NUMERIC"|"numeric") {return NUMERIC;}
("AND"|"and"|"OR"|"or") {return LOGIQUE;}
("NOT"|"not") {return NOT;}
[0-9]+ {yylval.intValue=atoi(yytext); return NB;}
[0-9]+.[0-9]+ {{yylval.floatValue=atof(yytext); return NUMERIC;}}
("<="|">="|"<"|">") {return COMP;}
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