%option noyywrap
%{
	#include<stdio.h>
%}
octint [o][0-7]+
hex [0][x|X][0-9A-F]+ 
decimal [0-9]+
float [-]?[0-9]+([.][0-9]+)?[e|E]([0-9]+)
idc [a-zA-Z"_"]+([a-zA-Z]|"_"|[0-9])*
stringpascal "'"[" "a-zA-Z0-9!?\/@#-]*"'"
stringc \"(\\.|[^"\\])*\"
commentc "/*"((\*+[^/*])|([^*]))*\**"*/"|[/]{1}[/]{1}.*
%%
{octint} printf("octa ");
{hex} printf("hex ");
{decimal} printf("decimal ");
{float} printf("float");
{idc} printf("identificateur c");
{stringpascal} printf("string pascal");
{stringc} printf("string c");
{commentc} printf("commentaire c");
.* printf("autre");
%%
int main(int argc, char *argv[])
{
    ++argv; --argc;
    if ( argc > 0 ) yyin = fopen( argv[0], "r" );
    else yyin = stdin;
	yylex();
	return 0;
}