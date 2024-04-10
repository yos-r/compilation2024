%{
    #include<stdio.h>
    int yylex(void);
void yyerror();
    int flag=0;
    extern FILE *yyin;
 
%}
%token NUMBER

%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%%
ArithmeticExpression: E{printf("\nResult=%d\n",$$);return 0;}
E:E'+'E {$$=$1+$3;}
 |E'-'E {$$=$1-$3;}
 |E'*'E {$$=$1*$3;}
 |E'/'E {$$=$1/$3;}
 |E'%'E {$$=$1%$3;}
 |'('E')' {$$=$2;}
 | NUMBER {$$=$1;}
;
%%
#include "lex.yy.c"
void main()
{
   FILE *fp; int i;
   fp=fopen("input.txt","r");
   yyin=fp;
 
 for(i=0;i<4;i++)
   yyparse();

  if(flag==0)
   printf("\nEntered arithmetic expression is Valid\n\n");

}
void yyerror()
{
   printf("\nEntered arithmetic expression is Invalid\n\n");
   flag=1;
}