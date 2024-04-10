/* SUJET SQL*/
%{
#include<stdio.h>
int yylex(void); 
int yyerror(char*s);
int champs=0;
%}
/* tokens definis par l'analyseur lexical*/
%token ID
%token FIN
%token PAROUV
%token PARFERM
%token SELECT
%token FROM
%token WHERE
%token COMP
%token NB
%token CREATE
%token INSERT
%token INTO

%%
CMD: SELECT listeselect '.' FIN
{printf(" champs selectionnes = %d \n",champs);}
|SELECT listeselect FROM ID WHERE ID COMP FIN
{printf(" champs selectionnes = %d",champs);}
listeselect : ID {champs+=1;}
| listeselect','ID {champs+=1;};
%%
#include "lex.yy.c" 
int yyerror(char *s){printf("%s \n",s);return 0;}
int main(int argc, char *argv[]){
    ++argv; --argc;
if ( argc > 0 ) yyin = fopen( argv[0], "r" );
else yyin = stdin;
for(int i=0;i<2;i++) {yyparse(); champs=0;}; /* specifier le nombre de lignes a traiter*/ 
return 0;}