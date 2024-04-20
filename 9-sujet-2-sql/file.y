/* SUJET SQL*/
%{
#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int yylex(void); 
int yyerror(char*s); 

int champs=0;
int colonnes=0;
#define MAX_STRINGS 100 
#define MAX_LENGTH 50  

char* strings[MAX_STRINGS];
char* tables[MAX_LENGTH]; //table des tables
int num_strings = 0;
int num_tables=0;

int is_string_in_array(char* strings[],char* str,int num_strings) {
    for (int i = 0; i < num_strings; i++) {
        if (strcmp(strings[i], str) == 0) {
            return 1;
        }
    }
    return 0; 
}

void add_string(char* strings[], char* str,int num_strings) {
    if (num_strings < MAX_STRINGS) {
        if (!is_string_in_array(strings,str,num_strings)) {
            strings[num_strings] = strdup(str);

        } else {
            printf("le champ '%s' est dupliqué \n", str);
        }
    } else {
        printf("Erreur '%s'.\n", str);
    }
}
void display_strings(char* strings[], int num_strings) {
    printf("Strings in the array:\n");
    for (int i = 0; i < num_strings; i++) {
        printf("%s\n", strings[i]);
    }
}
void empty_array(char* strings[] ,int numstrings) {
    for (int i = 0; i < num_strings; i++) {
        free(strings[i]);
        strings[i] = NULL; // Optional: Set pointers to NULL for safety
    }
    num_strings = 0; 
}
int countLines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1; 
    }

    int lines = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);
    return lines;
}
%}
%union
{
    int intValue;
    float floatValue;
    char *stringValue;
}
/* tokens definis par l'analyseur lexical*/
%token<stringValue> ID
%token <stringValue> STRING
%token PRIMARY_KEY
%token FIN
%token PAROUV
%token PARFERM
%token SELECT
%token FROM
%token WHERE
%token COMP
%token <intValue>NB
%token<floatValue> NUMERIC
%token CREATE
%token INSERT
%token INTO
%token TABLE
%token TYPE
%token VALUES
%token NULLL
%token POINTVIRGULE
%token COMMENT
%token UPDATE
%token DELETE

%%
/* # de champs selectionnes dans la requete 
detection des duplicats dans la selection/*/ 
S: CMD POINTVIRGULE | COMMENT {printf("ceci est un commentaire \n ");}| CMD error { yyerror("point virgule manquant"); }
CMD: SELECT listeselect 
{printf("champs selectionnes = %d ",champs);}
|SELECT listeselect FROM ID WHERE ID 
{printf(" champs selectionnes = %d ",champs);}
| CREATE TABLE ID PAROUV listecreation PARFERM  
{printf(" colonnes de la table %s = %d \n",$3,colonnes);add_string(tables,$3,num_tables);num_tables++;}
| CREATE TABLE error PAROUV listecreation PARFERM {yyerror("identifiant de la table à créer manquant");}
| INSERT INTO ID VALUES PAROUV listeinsertion PARFERM {if (is_string_in_array(tables,$3,num_tables))
{printf("\n");} 
else { printf("\n pas de table %s dans la base de données \n",$3);};
}
listeinsertion : listeinsertion ',' NUMERIC {printf("\n %f \n",$3);} 
| listeinsertion ',' STRING {printf("\n %s \n",$3);} 
| listeinsertion ',' NB {printf("\n %d \n",$3);} 
| NUMERIC {printf("\n %f \n",$1);} 
| STRING {printf("\n %s \n",$1);}
| NB {printf("\n %d \n",$1);}
listecreation : ID TYPE contrainte {colonnes+=1;add_string(strings, $1, num_strings);num_strings++;} 
| listecreation ',' ID TYPE {colonnes+=1;add_string(strings, $3, num_strings);num_strings++; };
listeselect : ID {champs+=1; add_string(strings, $1, num_strings); num_strings++;}
| listeselect','ID {champs+=1;add_string(strings, $3, num_strings);num_strings++;};
contrainte : /*  */ | PRIMARY_KEY  
%%

#include "lex.yy.c" 
int yyerror(char *s){printf("erreur: %s \n",s);return 0;}
int main(int argc, char *argv[]){
    ++argv; --argc;
if ( argc > 0 ) yyin = fopen( argv[0], "r" );
else yyin = stdin;
int lines=countLines("input.txt");
for(int i=0;i<lines;i++) {
    yyparse();
     champs=0; //detecteur du numero de champs selectionnes
     colonnes=0; // detecteur du numéro de champ a creer
     empty_array(strings,num_strings); //detecteur de duplicat
     num_strings=0;
     };

    display_strings(tables, num_tables);
     
return 0;}