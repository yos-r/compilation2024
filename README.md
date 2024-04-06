# ⭐Analyse lexicale avec Flex
## Installation de Flex
```
$ sudo install flex
```
## Execution d'un ``file.l``
```
$ flex file.l && gcc lex.yy.c -o exec && ./exec
```
## Execution avec arguments
```
$ flex file.l && gcc lex.yy.c -o exec && ./exec input.txt > output.txt
```
# ⭐Analyse syntaxique avec Bison
```
$ sudo install yacc
```
## Execution d'un ``file.y``
```
$ yacc -d file.y && gcc y.tab.c -o exec && ./exec
```
# ⭐Analyse syntaxique+lexicale avec Flex/Bison
```
$ flex file.l && yacc -d file.y && gcc y.tab.c -o exec && ./exec 
```


# Exemple: commandes réseau
## Analyse lexicale
 ### Unités lexicales `` file.l ``
 ```
 %option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
%}
routerconfig "config-router"
network "network"
hashtag "#"
area "area"
parouv "("
parferm ")"
point "."
nb [2][0-5][0-9]|[1][0-9][0-9]|[1-9][0-9]|[0-9]
id [a-zA-Z]([a-zA-Z]|[0-9])*
%%
{routerconfig} {return CONFIGROUTER;}
{hashtag} {return HASHTAG;}
{parouv} {return PAROUV;}
{parferm} {return PARFERM;}
{area} {return AREA; }
{network} {return NETWORK;}
{id} {return ID;}
{nb} {return NB;}
{point} {return POINT;}
[$] {return FIN;}
[\t \n]
%%
 ```

 ```
 $ flex file.l
 ```
 ### Analyse syntaxique ``file.y``
 ```
 %{
#include<stdio.h>
int yylex(void); 
int yyerror(char*s);
%}
%token HASHTAG
%token ID
%token FIN
%token PAROUV
%token PARFERM
%token CONFIGROUTER
%token NETWORK
%token NB
%token AREA
%token POINT

%%
S: CMD FIN {printf("commande correcte !");}
;
CMD: ID PAROUV CONFIGROUTER PARFERM HASHTAG NETWORK ADR ADR AREA NB ;
ADR: NB POINT NB POINT NB POINT NB;

%%
#include "lex.yy.c" 
int yyerror(char *s){
    printf("%s \n",s);
    return 0;
    }
int main(){
    yyparse();
    return 0;
    }
 ```

```
$ yacc -d file.y && gcc y.tab.c -o exec && ./exec
```

Exemple d'execution
````
> isiAriana ( config-router ) # network 255.255.255.0 255.0.0.0 area 2$  

> commande reseau correcte !
````