%{
#include<stdio.h>
int yylex(void);
int yyerror(char *s);
int n=0;
int m=0;
int p=0;

%}
%%
mot: S'$' {printf("n= %d , m= %d , p=%d ",n,m,p); getchar();}
;
S : 'a'S {n+=1;}
| B
;
B : 'b'B {m+=1;}
| C
;
C: 'c'C {p+=1;}
|
;
%%
int yylex()
{
char c=getchar();
if (c=='a'||c=='b'||c=='$'||c=='c') return(c);
else printf("erreur lexicale");
}
int yyerror(char *s){printf("%s \n",s);return 0;}
int main(){
/* a-Ecrire une grammaire pour anbmcp 
b-Rajouter les actions sémantiques pour compter et afficher n,m et p */
yyparse();
return 0;}