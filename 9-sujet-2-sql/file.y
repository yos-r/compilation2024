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

int is_string_in_array(char* strings[],char* str,int num_strings) {
    for (int i = 0; i < num_strings; i++) {
        if (strcmp(strings[i], str) == 0) {
            return 1;
        }
    }
    return 0; 
}

// Function to add a string to the array if it's not already present
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
    // Free memory allocated for each string
    for (int i = 0; i < num_strings; i++) {
        free(strings[i]);
        strings[i] = NULL; // Optional: Set pointers to NULL for safety
    }
    num_strings = 0; // Reset the array size to zero
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
%token FIN
%token PAROUV
%token PARFERM
%token SELECT
%token FROM
%token WHERE
%token COMP
%token NB
%token CREATE
%token INSERT
%token INTO
%token TABLE
%token TYPE
%token DECIMAL
%token POINTVIRGULE
%%
/* # de champs selectionnes dans la requete 
detection des duplicats dans la selection/*/ 
S: CMD POINTVIRGULE | CMD error { yyerror("point virgule manquant"); }
CMD: SELECT listeselect 
{printf("champs selectionnes = %d ",champs);}
|SELECT listeselect FROM ID WHERE ID 
{printf(" champs selectionnes = %d ",champs);}
| CREATE TABLE ID PAROUV listecreation PARFERM  
{printf(" colonnes de la table = %d \n",colonnes);add_string(tables,$3,1);}
| CREATE TABLE error PAROUV listecreation PARFERM {yyerror("dumbass");}
listecreation : ID TYPE {colonnes+=1;} 
| listecreation ',' ID TYPE {colonnes+=1; };

listeselect : ID {champs+=1; add_string(strings, $1, num_strings); num_strings++;}
| listeselect','ID {champs+=1;add_string(strings, $3, num_strings);num_strings++;};

%%

#include "lex.yy.c" 
int yyerror(char *s){printf("erreur: %s \n",s);return 0;}
int main(int argc, char *argv[]){
    ++argv; --argc;
if ( argc > 0 ) yyin = fopen( argv[0], "r" );
else yyin = stdin;
for(int i=0;i<2;i++) {
    yyparse();
    printf("\n");
     champs=0; //detecteur du numero de champs selectionnes
     colonnes=0; // detecteur du numéro de champ a creer
     empty_array(strings,num_strings); //detecteur de duplicat
     num_strings=0;};
     
return 0;}