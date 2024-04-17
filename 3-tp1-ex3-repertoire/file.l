/* tp1 ex3 repertoire */
%option noyywrap
%{
#include <stdio.h>
%} 
%%

[A-Z][a-zA-Z0-9]* { printf("Nom: %s\n", yytext); }

[a-z]+[a-zA-Z0-9]* { printf("Prénom(s): %s\n", yytext); }
[0-9]{2}" "[0-9]{2}" "[0-9]{2}" "[0-9]{2}" "[0-9]{2} { printf("Numéro de téléphone: %s \n", yytext); }
[ \t] ; 
\n      ;
.  { printf("Caractère non reconnu: %s\n", yytext); }

%%
int main(int argc, char *argv[])
{
    ++argv; --argc;
    if ( argc > 0 ) yyin = fopen( argv[0], "r" );
    else yyin = stdin;
	yylex();
	return 0;
}