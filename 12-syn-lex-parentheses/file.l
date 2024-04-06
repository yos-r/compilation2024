%{
	#include<stdio.h>
    #include "y.tab.h"
%}
%%
[0-9]+ {yylval=atoi(yytext);return NB;}
[a-zA-Z][a-zA-Z]* {return ID;}
[(] {return PAROUV;}
[)] {return PARFERM;}
[,] {return yytext[0];}
[$] {return FIN;}
[\t \n] {}
. {printf("Erreur");}
%%
int yywrap(){return 1;}