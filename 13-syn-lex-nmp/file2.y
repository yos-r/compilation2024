%{
#include<stdio.h>
int yylex(void);
int yyerror(char *s);
int n=0; //occur de a
int m=0; // occur de b
int p=0; //occur de c
int r=1; //occur de d

%}
%%
mot: S'd''$' {printf("n= %d m=%d p=%d r=%d ",n,m,p,r); getchar();}
;
S : 'a'S'd' {n+=1;r+=1;}
| B
;
B : 'b'B'd' {m+=1;r+=1;}
| C
;
C: 'c''c'C {p+=2;}
|
;
%%
int yylex()
{
char c=getchar();
if (c=='a'||c=='b'||c=='$'||c=='c'||c=='d') return(c);
else printf("erreur lexicale");
}
int yyerror(char *s){printf("%s \n",s);return 0;}
int main(){
/* -Ecrire une grammaire pour a^nb^mc^pd^r/p=2n et r=n+m+1 
b-Rajouter les actions sémantiques pour compter et afficher n,m ,p et d */
yyparse();
return 0;}