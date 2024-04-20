/* tp1- ex 5 - reconnaisseur des unités lexicales */
%option noyywrap
%{
	#include<stdio.h>
    #include <math.h>
    int nligne = 1;
    // fonction d'affichage de l'erreur 
    void yyerror (const char* msg,char* lexeme,int nligne);

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
[0-9]+[a-zA-Z_]+ {yyerror("identificateur mal formé",yytext,nligne);}
[-]?[0-9]*([.][0-9]+)?[e|E][^0-9] {yyerror("exposant attendu",yytext,nligne);}
\-[^0-9^\n]* {yyerror("nombre attendu ",yytext,nligne);}
{motcle} {printf("[%s] motcle \n",yytext);}
{chaine} {printf("[%s] chaine\n", yytext);}
\"[^\"\n]* yyerror(" chaine incomplete",yytext,nligne);
{identifiantc} {printf("[%s] ident \n",yytext);}
{commentaire} {printf("[%s] comment \n", yytext);}
\#.*[^#\n] {yyerror("Commentaire non fermé", yytext,nligne);}
[ \t]+
\n { nligne++; }
%%
void yyerror(const char *msg,char* lexeme,int nligne) {
    fprintf(stderr, "ERREUR LEXICALE:  [%s] : %s **ligne %d \n", lexeme, msg, nligne );
}
int main(int argc, char *argv[])
{
    ++argv; --argc;
    if ( argc > 0 ) yyin = fopen( argv[0], "r" );
    else yyin = stdin;
	yylex();
	return 0;
}