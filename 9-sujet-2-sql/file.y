/* SUJET SQL*/
%{
#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int yylex(void); 
int yyerror(char*s); 

int champs=0;
int colonnes=0;
int predicat=0;
#define MAX_STRINGS 100 
#define MAX_LENGTH 50  

char* strings[MAX_STRINGS];
char* tables[MAX_LENGTH]; //table des tables
int num_strings = 0;
int num_tables=0;
int num_ligne=1;
// HELP FUNCTIONS: manipulation des tableaux et des chaines
int is_string_in_array(char* strings[],char* str,int num_strings) {
    for (int i = 0; i < num_strings; i++) {
        if (strcmp(strings[i], str) == 0) {
            return 1;
        }
    }
    return 0; 
}

void add_string(char* strings[], char* str,int num_strings,int choix ) {
    if (num_strings < MAX_STRINGS) {
        if (!is_string_in_array(strings,str,num_strings)) {
            strings[num_strings] = strdup(str);

        } else {
            switch (choix){
                  case 0: printf("Erreur: ligne %d : le champ '%s' est dupliqué \n", num_ligne,str); break;
                  case 1: printf("Erreur: ligne %d : la table '%s' existe déja \n", num_ligne,str);break;
                   }
            exit(EXIT_FAILURE); 
        }
    } else {
        printf("Erreur '%s'.\n", str);
    }
}
void delete_string(char* strings[], char* str, int num_strings) {
    int i, j;
    for (i = 0; i < num_strings; i++) {
        if (strcmp(strings[i], str) == 0) {
            // Found the string to delete
            // Shift all elements after the deleted element one position to the left
            for (j = i; j < (num_strings - 1); j++) {
                strings[j] = strings[j + 1];
            }
            return; 
        }
    }
    // String not found
    printf("String '%s' not found in the array.\n", str);
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
%token FOREIGN_KEY
%token REFERENCES
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
%token INT
%token VARCHAR
%token VALUES
%token NULLL
%token POINTVIRGULE
%token COMMENT
%token UPDATE
%token DELETE
%token SET
%token ALL
%token DROP
%token EGAL
%token DIFF
%token LOGIQUE
%token NOT
%type <intValue> condition

%%
/* axiome */ 
S: CMD POINTVIRGULE 
| COMMENT {printf("Ligne %d : Commentaire \n ",num_ligne);}
| CMD error { printf("Erreur Ligne %d : point virgule manquant \n",num_ligne); exit(EXIT_FAILURE);}
CMD: 
/* selection */
SELECT choix FROM ID condition {if (is_string_in_array(tables,$4,num_tables)) {printf("Ligne %d : Sélection réussie depuis la table %s \n",num_ligne,$4);} 
        else { printf("Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,$4); exit(EXIT_FAILURE); };}
| SELECT error { printf("Erreur ligne %d: Identifiant manquant ou mal formé \n",num_ligne); exit(EXIT_FAILURE); };
/* creation d'une table */
| CREATE TABLE ID PAROUV listecreation PARFERM  {add_string(tables,$3,num_tables,1); printf(" Ligne %d: Colonnes de la table %s = %d \n",num_ligne,$3,colonnes);num_tables++;printf("Ligne %d : Création de la table %s réussie \n",num_ligne,$3);}
| CREATE TABLE error PAROUV listecreation PARFERM {printf("Erreur Ligne %d : Identifiant manquant \n",num_ligne); exit(EXIT_FAILURE);}
| CREATE error ID PAROUV listecreation PARFERM {printf("Erreur Ligne %d : mot-cle TABLE oublié \n",num_ligne); exit(EXIT_FAILURE);}
/* insertion de lignes */
| INSERT INTO ID VALUES PAROUV listeinsertion PARFERM {if (is_string_in_array(tables,$3,num_tables)) {printf("Ligne %d : Insertion réussie dans la table %s \n",num_ligne,$3);} 
        else { printf(" Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,$3); exit(EXIT_FAILURE); };}
/* mise à jour d'une table */
| UPDATE ID SET ID EGAL value {if (is_string_in_array(tables,$2,num_tables)) {printf("Ligne %d : Mise à jour de la table %s réussie \n",num_ligne,$2);} else {printf("Erreur Ligne %d : La table %s n'existe pas ",num_ligne,$2); exit(EXIT_FAILURE);}}
| UPDATE ID SET error EGAL value  {printf("Erreur Ligne %d : Identifiant manquant ou mal formé ",num_ligne); exit(EXIT_FAILURE);}
| UPDATE error SET error EGAL value  {printf("Erreur Ligne %d : Identifiant manquant ou mal formé ",num_ligne); exit(EXIT_FAILURE);}
| UPDATE ID SET ID error value  {printf("Erreur Ligne %d : Opérateur incorrect, la mise à jour est effectuée avec = ",num_ligne); exit(EXIT_FAILURE);}
| UPDATE ID SET ID EGAL error {printf("Erreur Ligne %d : ",num_ligne); exit(EXIT_FAILURE);}
/* Suppression d'une table */
| DROP TABLE ID {if (is_string_in_array(tables,$3,num_tables)) { delete_string(tables,$3,num_tables); num_tables--;printf("Ligne %d : Suppression de la table %s réussie\n",num_ligne,$3);} 
        else { printf(" Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,$3); exit(EXIT_FAILURE); };}
| DROP error ID {printf("Erreur Ligne %d : mot-cle TABLE oublié \n",num_ligne); exit(EXIT_FAILURE);}
| DROP TABLE error {printf("Erreur Ligne %d : Identifiant manquant ou mal formé ",num_ligne); exit(EXIT_FAILURE);}
/* suppression de lignes d'une table */
| DELETE FROM ID condition {if (is_string_in_array(tables,$3,num_tables)) { if ($4==1) {printf("Ligne %d : La table %s est vidée \n",num_ligne,$3);}; printf("Ligne %d : Suppression de lignes réussie depuis la table %s \n",num_ligne,$3);} 
        else { printf(" Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,$3); exit(EXIT_FAILURE); };}
/* choix de selection */
choix: ALL {printf(" Ligne %d: Tous les champs selectionnes\n",num_ligne);}
| listeselect {printf(" Ligne %d: Champs selectionnes = %d \n",num_ligne,champs);}
/* condition dans les requetes */
condition: WHERE listecondition  {$$=0; if (predicat>1) printf("Ligne %d: %d prédicats dans la clause \n",num_ligne,predicat);} |  {$$=1;};
listecondition: listecondition LOGIQUE ID op value {predicat++;}
| ID op value {predicat++;} 
/* opérateurs de comparaison */
op: EGAL | DIFF | COMP ;
/* valeurs possibles  */
value: NB | STRING | NUMERIC;
/* liste insertion  */
listeinsertion : listeinsertion ',' NUMERIC {} 
| listeinsertion ',' STRING {} 
| listeinsertion ',' NB {} 
| NUMERIC {} 
| STRING {}
| NB {}
| listeinsertion ',' error { printf("Erreur ligne %d: Erreur d'insertion \n",num_ligne); exit(EXIT_FAILURE); }
/* liste creation  */
listecreation : ID type contrainte {colonnes+=1;add_string(strings, $1, num_strings,0);num_strings++;} 
| listecreation ',' ID type {colonnes+=1;add_string(strings, $3, num_strings,0);num_strings++; };
| listecreation ',' FOREIGN_KEY PAROUV ID PARFERM  REFERENCES ID PAROUV ID PARFERM {if (!is_string_in_array(tables,$8,num_tables)) {printf("Erreur Ligne %d : table %s n'existe pas \n",num_ligne,$8); exit(EXIT_FAILURE);} else { colonnes+=1;add_string(strings, $5, num_strings,0);num_strings++; }};
| FOREIGN_KEY PAROUV ID PARFERM REFERENCES ID PAROUV ID PARFERM {colonnes+=1;add_string(strings, $3, num_strings,0);num_strings++; };
/* types de champs des tables */
type: VARCHAR PAROUV NB PARFERM {if ($3>255) {printf("Erreur ligne %d : taille de la chaine excède 255",num_ligne);exit(EXIT_FAILURE);}} 
| INT 
| VARCHAR  {printf("Erreur ligne %d : taille de la chaine non spécifiée ",num_ligne);exit(EXIT_FAILURE);} 
| VARCHAR error NB  {printf("Erreur ligne %d : parenthèse ouvrante oubliée ",num_ligne);exit(EXIT_FAILURE);} 
| NUMERIC PAROUV NB ',' NB PARFERM
| error {printf("Erreur ligne %d : Type non reconnu \n ",num_ligne);}
/* liste selection  */
listeselect : ID {champs+=1; add_string(strings, $1, num_strings,0); num_strings++;}
| listeselect','ID {champs+=1;add_string(strings, $3, num_strings,0);num_strings++;}
| listeselect error ID { printf("Erreur ligne %d: Virgule manquante \n",num_ligne); exit(EXIT_FAILURE); };
/* contrainte optionnelle  */
contrainte :  | PRIMARY_KEY  | error {printf("Erreur ligne %d : contrainte non valide ",num_ligne);exit(EXIT_FAILURE);}
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
    // réinitialisation des variables à chaque nouvelle commande
     champs=0; //detecteur du numero de champs selectionnes
     colonnes=0; // detecteur du numéro de champ a creer
     empty_array(strings,num_strings); //vider le tableau de detection des champs dupliqués
     num_strings=0;
     num_ligne++; //incrémentation du nombre de lignes
     predicat=0; // compteur des predicats
     };
    
    /* display_strings(tables, num_tables);
    add_string(tables,"fsadf",1,0);
    delete_string(tables,"asd",2);  */
    display_strings(tables, num_tables);

return 0;}