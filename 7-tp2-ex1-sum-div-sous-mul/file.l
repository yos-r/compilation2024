/* tp 2 exercice 1 */
%{
#include<stdio.h>
#include<math.h>
#include"y.tab.h"
%}
%%
[0-9]+ {yylval=atoi(yytext); return NB;}
produit {return PROD;}
somme {return SOM;}
soustraction {return SOUS;}
division {return DIVISION;}
[,|.] {return yytext[0];}
[$] {return FIN;}
[ \t\n] {}
. {printf("Erreur");}
%%
int yywrap()
{return 1;}
