%option noyywrap
%{
	#include<stdio.h>
    #include <string.h>
%}
chiff [0-9]+
id [a-zA-Z][a-zA-Z0-9]*
stringc \"(\\.|[^"\\])*\"
comment "/*"((\*+[^/*])|([^*]))*\**"*/"|[/]{1}[/]{1}.*
fonctionexpression [a-z]*"("([^,")"\"]|,)*
%%
{fonctionexpression} printf("%s \n",strtok(yytext,"("));
{comment} ;
{chiff} ;
{id} ;
{stringc} ;
[;{}+")",] ;
[ \t\n] ;
%%
//on devra obtenir la liste suivante: plus main printf plus getchar 
void main(int argc, char *argv[]){
++argv; --argc;
if ( argc > 0 ) yyin = fopen( argv[0], "r" );
else yyin = stdin;
yylex();
}