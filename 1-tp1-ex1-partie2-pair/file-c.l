/* tp1 -ex1 - partie 2- questions 5 et 6 */
%option noyywrap
%{	
	#include<stdio.h>
%}
pairpair (aa|bb)*((ab|ba)(aa|bb)*(ab|ba)(aa|bb)*)*
nonpair a*b*
/* ajout de l'UL identificateur */
id [a-zA-Z][a-zA-Z0-9]* 
nb [0-9]+
%%
{nonpair} {printf("[%s]: des a d\'abord et des b ensuite",yytext); };
{pairpair} printf("[%s]: nombre pair de a et de b",yytext);
{id} printf("[%s]: identificateur",yytext);
{nb} printf("[%s]: entier",yytext);
.* printf("autre");
%%
int main(int argc, char *argv[])
{
++argv; --argc; 
if ( argc > 0 ) yyin = fopen( argv[0], "r" ); else yyin = stdin;
yylex();
return 0;
}