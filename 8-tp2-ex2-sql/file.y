%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex(void);
int yyerror(char *s);
%}
%token <chaine> CREATE    
%token <chaine> TABLE
%token <chaine> TYPE
%token <entier> NUMBER
%token <chaine> IDENTIFIER
%token <chaine> COMMA
%token <chaine> PAROUV
%token <chaine> PARFERM
%union
{
int entier ;
double reel ;
char *chaine ;
}
%%
T : C {printf("requete SQL valide"); YYACCEPT;}
;
C: CREATE TABLE IDENTIFIER PAROUV D PARFERM 
;
D: IDENTIFIER TYPE PAROUV NUMBER PARFERM COMMA D 	
| IDENTIFIER TYPE PAROUV NUMBER PARFERM				
;
%%
#include "lex.yy.c"
int yyerror(char *s)
{
printf ("%s", s);
return (0);
}
int main(int argc, char *argv[])
{
    // ./0000 input.txt
    ++argv; --argc;
    if ( argc > 0 ) yyin = fopen( argv[0], "r" );
    else yyin = stdin;
	yyparse();
	return 0;
}