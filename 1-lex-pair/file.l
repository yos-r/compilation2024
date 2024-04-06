%option noyywrap
%{	
	#include<stdio.h>
%}
pairpair (aa|bb)*((ab|ba)(aa|bb)*(ab|ba)(aa|bb)*)*
nonpair a*b*
%%
{nonpair} {printf("[%s]: des a d\'abord et des b ensuite",yytext); };
{pairpair} printf("[%s]: nombre pair de a et de b",yytext);
.* printf("autre");
%%
int main(int argc, char *argv[])
{
++argv; --argc; 
if ( argc > 0 ) yyin = fopen( argv[0], "r" ); else yyin = stdin;
yylex();
return 0;
}