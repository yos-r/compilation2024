%{
#include<stdio.h>
int yylex(void); 
int yyerror(char*s);
%}
%token SQL
%token ID
%token FIN
%token PAROUV
%token PARFERM

%%
S: CMD FIN {printf("syntaxiquement correct!");}
;
CMD: SQL PAROUV ID PARFERM ;

%%
#include "lex.yy.c" 
int yyerror(char *s){printf("%s \n",s);return 0;}
int main(){yyparse();return 0;}