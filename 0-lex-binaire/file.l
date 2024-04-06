
%{
	#include<stdio.h>
%}
binaire (0|1)+
%% 
{binaire} printf(" %s est un nombre binaire \n",yytext);
.* printf("%s n\'est pas un nombre binaire \n", yytext);
%%
int yywrap(){ return 1;}

 int main(int argc, char *argv[])
{
	++argv; --argc;
	
	if ( argc > 0 ) yyin = fopen( argv[0], "r" ); else yyin = stdin; 

	yylex() ;
}