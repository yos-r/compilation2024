%{
#include<stdio.h>
int yylex(void);
int yyerror(char*s);
int nimbriq=0;
int npar=0;
%}
%token FIN;
%token ID;
%token PAROUV;
%token PARFERM;
%token NB;
%% 
mot: S FIN {printf(" niveau: %d ",nimbriq); printf(" nparentheses: %d ",npar);} 
;
S : PAROUV S PARFERM S {nimbriq+=1;npar+=2;}
| 
;
%%
#include "lex.yy.c"
int yyerror(char *s){printf("%s \n",s);return 0;}
int main(){
//1. Ecrire une grammaire permettant de déterminer le niveau d’imbrication des parenthèses dans un 
//système de parenthèses bien formé.  
//2. Rajouter les actions sémantiques pour compter les parenthèses
yyparse();
return 0;}