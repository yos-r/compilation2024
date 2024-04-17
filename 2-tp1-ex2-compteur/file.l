/* TP1 EX2 COMPTEUR MOTS/LIGNES/CHARS/ SOMME DES NOMBRES LUS */
%option noyywrap
%{
	#include<stdio.h>
    // initialisation
    int nmots=0;
    int nlignes=1;
    int ncar=0;
    int somme=0;
%}
mot [a-zA-Z]+
nombre [0-9]+
ligne \n
%%
{mot} nmots++; ncar+=yyleng;
{ligne} nlignes++;ncar+=yyleng;
{nombre} somme+=atof(yytext);ncar+=yyleng;
. ncar++;
%%
int main(int argc, char *argv[])
{
    ++argv; --argc;
    if ( argc > 0 ) yyin = fopen( argv[0], "r" );
    else yyin = stdin;
	yylex();
    printf("Le nombre de mots est %d \n ",nmots);
    printf("Le nombre de lignes est %d \n",nlignes);
    printf("La somme des entiers est: %d \n",somme );
    printf("Le nombre de caracteres est %d \n",ncar);
	return 0;
}