/* TP1 EX4 analyseur requete SQL */
%option noyywrap
%{
	#include<stdio.h>
%}
id [a-zA-Z][a-zA-Z0-9_]*
%%

CREATE|create { printf("CREATE "); }
"PRIMARY KEY" {printf("PRIMARY_KEY ");}
TABLE|table { printf("TABLE "); }
INT|int|DATE|date|VARCHAR|varchar|NUMBER|number { printf("DATATYPE "); }
{id} { printf("IDENTIFIER "); }
"("  {printf("%s ",yytext);}
")"  {printf("%s ",yytext);}
"," {printf("COMMA ");}
[0-9]+ {printf("NUMBER ");}
. ;
%%
int main(int argc, char *argv[])
{
    ++argv; --argc;
    if ( argc > 0 ) yyin = fopen( argv[0], "r" );
    else yyin = stdin;
	yylex();
	return 0;
}