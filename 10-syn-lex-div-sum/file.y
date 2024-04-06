%{
#include<stdio.h>
int yylex(void);
int yyerror(char *s);
int somme=0;
int produit=1;
int sous=0;
float division=1;
%}
%token NB
%token FIN
%token PROD
%token SOM
%token DIVISION
%token SOUS
%%
liste:FIN {printf("correct"); }
|SOM listesom'.'liste  {printf(" somme = %d",somme);};
|PROD listeprod'.'liste {printf(" produit = %d",produit);};
|DIVISION listediv'.'liste {printf(" division =%f",division);} ;
|SOUS listesous'.'liste {printf(" soustraction = %d",sous);} ;
listesom: NB {somme +=$1;}|listesom','NB {somme+=$3;}; 
listeprod: NB {produit *=$1;}|listeprod','NB {produit *= $3;};
listesous: NB {sous =$1;}| listesous','NB {sous-=$3;}; 
listediv: NB {division=$1;}| listediv','NB  {division/=$3;} ;
%%
#include "lex.yy.c"
int yyerror(char *s){printf ("%s", s); return (0);}
int main(){yyparse();getchar();}
