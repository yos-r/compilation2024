%option noyywrap
%{	
	#include<stdio.h>
%}
%%
"/*" printf("<SE>");
"*/" printf("<ASE>");
"\\n" printf("<ASN>");
"("|")" printf("<PO>");
"?"+ printf("<?,%d>",yyleng);
. printf("autre");

%%
// code c, au dessus-> regles de traduction
int main(int argc, char *argv[])
{
yylex();
	return 0;
}