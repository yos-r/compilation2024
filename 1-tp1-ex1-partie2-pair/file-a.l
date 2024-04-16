/* tp1 -ex1 - partie 2- questions 1 et 2 */
%option noyywrap
%{	
	#include<stdio.h>
%}
pairpair (aa|bb)*((ab|ba)(aa|bb)*(ab|ba)(aa|bb)*)*
nonpair a*b*
%%
{pairpair} printf("[%s]: nombre pair de a et de b",yytext);
{nonpair} {printf("[%s]: des a d\'abord et des b ensuite",yytext); };
.* printf("autre");
%%
int main(int argc, char *argv[])
{
++argv; --argc; 
if ( argc > 0 ) yyin = fopen( argv[0], "r" ); else yyin = stdin;
yylex();
return 0;
}