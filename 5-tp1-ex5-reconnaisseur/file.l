/* tp1- ex 5 - reconnaisseur des unités lexicales */
%option noyywrap
%{
	#include<stdio.h>
    #include <math.h>
    int nligne = 1;

%}
entier [0-9]+
reel [-]?[0-9]*([.][0-9]+)?[e|E]([0-9]+)|[0-9]+[.][0-9]
motcle ("if"|"else"|"while")
identifiantc [a-zA-Z_][a-zA-Z0-9_]*
affect ":="
op_rel ("<"|">"|">="|"=="|"!="|"<=")
op_arith ("+"|"-"|"*"|"/")
chaine \"[^\"\n]*\"
commentaire \#.*\#
%%
{entier} {printf("[%s] entier \n ",yytext);}
{op_rel} {printf("[%s] op_rel \n",yytext);}
{op_arith} {printf("[%s] op_arith \n",yytext);}
{affect} {printf("[%s] affect \n",yytext);}
{reel} {double value = atof(yytext); printf("[%s] reel %f \n",yytext,value); }
[0-9]+[a-zA-Z_]+ {printf("[%s] identificateur mal formé , erreur ligne %d \n",yytext,nligne);}
[-]?[0-9]*([.][0-9]+)?[e|E][^0-9] {printf("[%s] exposant attendu, erreur ligne %d \n",yytext,nligne);}
\-[^0-9^\n]* {printf("[%s] nombre attendu , ligne %d \n",yytext,nligne);}
{motcle} {printf("[%s] motcle \n",yytext);}
{chaine} {printf("[%s] chaine\n", yytext);}
\"[^\"\n]* printf("[%s] chaine incomplete ** erreur ligne %d \n",yytext,nligne);
{identifiantc} {printf("[%s] ident \n",yytext);}
{commentaire} {printf("[%s] comment \n", yytext);}
\#.*[^#\n] {printf("[%s]  pas de '#' à la fin ** erreur ligne %d \n", yytext,nligne);}
[ \t]+
\n { nligne++; }
%%
int main(int argc, char *argv[])
{
    ++argv; --argc;
    if ( argc > 0 ) yyin = fopen( argv[0], "r" );
    else yyin = stdin;
	yylex();
	return 0;
}