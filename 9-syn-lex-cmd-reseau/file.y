%{
#include<stdio.h>
int yylex(void); 
int yyerror(char*s);
%}
%token HASHTAG
%token ID
%token FIN
%token PAROUV
%token PARFERM
%token CONFIGROUTER
%token NETWORK
%token NB
%token AREA
%token POINT
%%
S: CMD FIN {printf("commande reseau correcte !");}
;
CMD: ID PAROUV CONFIGROUTER PARFERM HASHTAG NETWORK ADR ADR AREA NB ;
ADR: NB POINT NB POINT NB POINT NB;
%%
#include "lex.yy.c" 
int yyerror(char *s){printf("%s \n",s);return 0;}
int main(){yyparse();return 0;}