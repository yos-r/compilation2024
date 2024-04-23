/* SUJET SQL
/* SUJET SQL: Yosr BARGHOUTI et Mariem BEN SALAH 1 ING 01*/

%{
#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int yylex(void); 
int yyerror(char*s); 


#define MAX_STRINGS 100 
#define MAX_LENGTH 50  
#define MAX_KEYS 10    


char* strings[MAX_STRINGS];
char* types[MAX_STRINGS];
char* tables[MAX_LENGTH]; //table des tables

int num_strings = 0; // chaines dans les requetes
int num_types=0; // types dans les requetes de creation
int num_champs=0; // nombre de champs
int champs=0; // nombre de champs
int colonnes=0; // nombre de colonnes
int predicat=0; //nombre de predicats 
int num_tables=0; // nombre de tables
int num_ligne=1; // nombre de ligne


// ⭐⭐ enregistrement cle valeur pour stocker les tables et les nombs de champs
struct KeyValue {
    char key[100]; // Assuming maximum length of the key is 100 characters
    char champs[MAX_LENGTH][100]; // Assuming maximum length of each value is 100 characters
    char types[MAX_LENGTH][100];
    int num_values; // Number of values in the array
};
int cle=0; //nombre de clés/ enregistrements dans tablesChamps
struct KeyValue tablesChamps[MAX_KEYS]; // tableau d'enregistrement: décrit la base de données


// HELP FUNCTIONS: manipulation des tableaux et des chaines

// verifie si une chaine appartient a un tableau
int is_string_in_array(char* strings[],char* str,int num_strings) {
    for (int i = 0; i < num_strings; i++) {
        if (strcmp(strings[i], str) == 0) {
            return 1;
        }
    }
    return 0; 
}
// ⭐⭐ affichage de la table des champs
void displayArray(struct KeyValue array[], int size) {
    for (int i = 0; i < size; i++) {
         if (is_string_in_array(tables,array[i].key,num_tables)){

        // printf("Struct %d:\n", i + 1);
        printf("Table: %s\n", array[i].key);
        printf("    Champs:\n");
        for (int j = 0; j < array[i].num_values; j++) {
            printf("        %s\n", array[i].champs[j]);
        }
        printf("    Types:\n");
        for (int j = 0; j < array[i].num_values; j++) {
            printf("        %s\n", array[i].types[j]);
        }
        printf("\n");
        }
    }
}

// ⭐⭐ verifie si toutes les chaines d'un tableau existent dans un autre tableau
int are_all_values_in_types(char* table, char types[][100], int types_size, char* strings[], int num_strings) {
    for (int i = 0; i < num_strings; i++) {
        int found = 0;
        for (int j = 0; j < types_size; j++) {
            if (strcmp(strings[i], types[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Erreur ligne %d: Le champ ' %s '  n'existe pas dans la table %s \n",num_ligne,strings[i],table);
            exit(EXIT_FAILURE);
            return 0; // Not all values found in types array
        }
    }
    return 1; // All values found in types array
}
// affichage des champs d'un enreigstrement clé valeur
void display_champs(struct KeyValue kv) {
    printf("value array for key '%s':\n", kv.key);
    for (int i = 0; i < kv.num_values; i++) {
        printf("%s\t", kv.champs[i]);
    }
}
//ajout d'une chaine dans une table de chaine avec verification de duplicat: declenche une erreur
void add_string(char* strings[], char* str,int num_strings,int choix ) {
    if (num_strings < MAX_STRINGS) {
        if (!is_string_in_array(strings,str,num_strings)) {
            strings[num_strings] = strdup(str);

        } else {
            switch (choix){
                  case 0: printf("Erreur: ligne %d : le champ '%s' est dupliqué \n", num_ligne,str); break;
                  case 1: printf("Erreur: ligne %d : la table '%s' existe déja \n", num_ligne,str);break;
                   }
            if (choix!=2) exit(EXIT_FAILURE); 
        }
    } else {
        printf("Erreur '%s'.\n", str);
    }
}
// verfie si un champ  existe dans une table ou non
int check_field_array(struct KeyValue array[], char *table,char* field,int size){
    for (int i = 0; i < size; i++) {
        if (strcmp(array[i].key, table) == 0) {
            // table trouv'ee, recchercher dans les champs
             for (int j = 0; j < array[i].num_values; j++){
                if (strcmp(array[i].champs[j],field)==0) {
                    return 1;
                }
             }
        }
    }
    printf("Erreur ligne %d: Le champ ' %s '  n'existe pas dans la table %s \n",num_ligne,field,table);
    exit(EXIT_FAILURE); 
    return -1;
}
//ajout simple d'une chaine dans une table de chaine sans verification de duplicat
void add_string2(char* strings[], char* str,int num_strings ) {
    if (num_strings < MAX_STRINGS) {
        strings[num_strings] = strdup(str);}
}
//suppression d'une chaine d'un tableau
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
// trouve la cle de la table dans le tableau d'entregistement
int findKey(struct KeyValue array[], char *searchKey,int size){
    for (int i = 0; i < size; i++) {
        if (strcmp(array[i].key, searchKey) == 0) {
            return i; 
        }
    }
    return -1;
}
// affichage simple d'un tableau  de chaines
void display_strings(char* strings[], int num_strings) {
    printf("Affichage des chaines du tableau:\n");
    for (int i = 0; i < num_strings; i++) {
        printf("%s\n", strings[i]);
    }
}
// vider un tableau
void empty_array(char* strings[] ,int numstrings) {
    for (int i = 0; i < num_strings; i++) {
        free(strings[i]);
        strings[i] = NULL; // Optional: Set pointers to NULL for safety
    }
    num_strings = 0; 
}
//compter le nombre de lignes dans un fichier txt
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
%token NUMERICTYPE
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
%token DESCRIBE
%type <intValue> condition
%type <stringValue> type
%type <intValue> choix

%%
/* axiome */ 
S: CMD POINTVIRGULE 
| COMMENT {printf("Ligne %d : Commentaire \n ",num_ligne);}
| CMD error { printf("Erreur Ligne %d : point virgule manquant \n",num_ligne); exit(EXIT_FAILURE);}

CMD: 
DESCRIBE {printf("Ligne %d : Description de la base de donnees \n",num_ligne); displayArray(tablesChamps,cle);}
|/* selection */
SELECT choix FROM ID condition {if (is_string_in_array(tables,$4,num_tables)) {
    int key=findKey(tablesChamps,$4,cle);
        int result = are_all_values_in_types($4,tablesChamps[key].champs, tablesChamps[key].num_values, strings,num_strings);
        if ($2==0){printf("Ligne %d : %d Champs selectionnes \n ",num_ligne,tablesChamps[key].num_values);}
 printf("Ligne %d : Sélection réussie depuis la table %s \n",num_ligne,$4);} 
        else { printf("Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,$4); exit(EXIT_FAILURE); };}
| SELECT error { printf("Erreur ligne %d: Identifiant manquant ou mal formé \n",num_ligne); exit(EXIT_FAILURE); };
/* creation d'une table */
| CREATE TABLE ID PAROUV listecreation PARFERM  {add_string(tables,$3,num_tables,1); printf(" Ligne %d: Colonnes de la table %s = %d \n",num_ligne,$3,colonnes);num_tables++;
printf("Ligne %d : Création de la table %s réussie \n",num_ligne,$3);
strcpy(tablesChamps[cle].key, $3);tablesChamps[cle].num_values=num_strings;cle++;
}
| CREATE TABLE error PAROUV listecreation PARFERM {printf("Erreur Ligne %d : Identifiant manquant \n",num_ligne); exit(EXIT_FAILURE);}
| CREATE error ID PAROUV listecreation PARFERM {printf("Erreur Ligne %d : mot-cle TABLE oublié \n",num_ligne); exit(EXIT_FAILURE);}
/* insertion de lignes */
| INSERT INTO ID VALUES PAROUV listeinsertion PARFERM {if (is_string_in_array(tables,$3,num_tables)) {int clef= findKey(tablesChamps,$3,cle); printf("le nombre de champs %d ",num_champs); /* chercher la cle*/if (num_champs==tablesChamps[clef].num_values) printf("Ligne %d : Insertion réussie dans la table %s \n",num_ligne,$3); else {printf("Erreur Ligne %d : La table %s possede %d colonnes, vous avez fourni %d ",num_ligne,$3,tablesChamps[clef].num_values,num_champs); exit(EXIT_FAILURE);};} 
        else { printf(" Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,$3); exit(EXIT_FAILURE); };}
/* mise à jour d'une table */
| UPDATE ID SET ID EGAL value {if (is_string_in_array(tables,$2,num_tables)) {int a= check_field_array(tablesChamps,$2,$4,cle);printf("Ligne %d : Mise à jour de la table %s réussie \n",num_ligne,$2);} else {printf("Erreur Ligne %d : La table %s n'existe pas ",num_ligne,$2); exit(EXIT_FAILURE);}}
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
| DELETE FROM ID condition {if (is_string_in_array(tables,$3,num_tables)) {
    int key=findKey(tablesChamps,$3,cle);
        int result = are_all_values_in_types($3,tablesChamps[key].champs, tablesChamps[key].num_values, strings,num_strings);
     if ($4==1) {printf("Ligne %d : La table %s est vidée \n",num_ligne,$3);}; printf("Ligne %d : Suppression de lignes réussie depuis la table %s \n",num_ligne,$3);} 
        else { printf(" Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,$3); exit(EXIT_FAILURE); };}
/* choix de selection */
choix: ALL {$$=0; }
| listeselect {$$=1;printf(" Ligne %d: Champs selectionnes = %d \n",num_ligne,champs);}
/* condition dans les requetes */
condition: WHERE listecondition  {$$=0; if (predicat>1) printf("Ligne %d: %d prédicats dans la clause \n",num_ligne,predicat);} |  {$$=1;};
listecondition: listecondition LOGIQUE not ID op value {predicat++;add_string2(strings, $4, num_strings); num_strings++;}
| not ID op value {predicat++; add_string2(strings, $2, num_strings); num_strings++;} 
not: NOT | ; 
/* opérateurs de comparaison */
op: EGAL | DIFF | COMP ;
/* valeurs possibles  */
value: NB | STRING | NUMERIC;
/* liste insertion  */
listeinsertion : listeinsertion ',' NUMERIC {printf("%f ",$3); num_champs++;} 
| listeinsertion ',' STRING {printf("%s ",$3);num_champs++;} 
| listeinsertion ',' NB {printf("%d ",$3);num_champs++;} 
| NUMERIC {printf("%f ",$1);num_champs++;} 
| STRING {printf("%s ",$1);num_champs++;}
| NB {printf("%d ",$1);num_champs++;}
| listeinsertion ',' error { printf("Erreur ligne %d: Erreur d'insertion \n",num_ligne); exit(EXIT_FAILURE); }
/* liste creation  */
listecreation : ID type contrainte {colonnes+=1;add_string(strings, $1, num_strings,0);strcpy(tablesChamps[cle].champs[num_strings], $1);num_strings++;
add_string2(types, $2, num_types);strcpy(tablesChamps[cle].types[num_types], $2);num_types++; } 
| listecreation ',' ID type contrainte {colonnes+=1;add_string(strings, $3, num_strings,0);strcpy(tablesChamps[cle].champs[num_strings], $3);num_strings++;
add_string2(types, $4, num_types);strcpy(tablesChamps[cle].types[num_types], $4);num_types++;
};
| listecreation ',' FOREIGN_KEY PAROUV ID PARFERM  REFERENCES ID PAROUV ID PARFERM {if (!is_string_in_array(tables,$8,num_tables)) {printf("Erreur Ligne %d : table %s n'existe pas \n",num_ligne,$8); exit(EXIT_FAILURE);} else { 
int i= check_field_array(tablesChamps,$8,$10,cle);
colonnes+=1;
add_string(strings, $5, num_strings,0);strcpy(tablesChamps[cle].champs[num_strings], $5); num_strings++; 
add_string2(types, "FOREIGN", num_types);strcpy(tablesChamps[cle].types[num_types], "FOREIGN");num_types++; }};
| FOREIGN_KEY PAROUV ID PARFERM REFERENCES ID PAROUV ID PARFERM {if (!is_string_in_array(tables,$6,num_tables)) {printf("Erreur Ligne %d : table %s n'existe pas \n",num_ligne,$6); exit(EXIT_FAILURE);};
colonnes+=1;
int i= check_field_array(tablesChamps,$6,$8,cle);
add_string(strings, $3, num_strings,0);num_strings++; 
add_string(types, "FOREIGN", num_types,2);num_types++;};
/* types de champs des tables */
type: VARCHAR PAROUV NB PARFERM {if ($3>65535 ) {printf("Erreur ligne %d : taille de la chaine excède 65,535 ",num_ligne);exit(EXIT_FAILURE);} else {$$="VARCHAR";}} 
| INT {$$="INT";}
| NUMERICTYPE PAROUV NB  PARFERM {$$="NUMERIC";}
| VARCHAR  {printf("Erreur ligne %d : taille de la chaine non spécifiée ",num_ligne);exit(EXIT_FAILURE);} 
| VARCHAR error NB  {printf("Erreur ligne %d : parenthèse ouvrante oubliée ",num_ligne);exit(EXIT_FAILURE);} 
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
int lines=countLines(argv[0]);
for(int i=0;i<lines;i++) {
    yyparse();
    // réinitialisation des variables à chaque nouvelle commande
     champs=0; //detecteur du numero de champs selectionnes
     colonnes=0; // detecteur du numéro de champ a creer
     empty_array(strings,num_strings); //vider le tableau de detection des champs dupliqués
      empty_array(types,num_types);//vider le tableau de types des champs de la table
     num_strings=0;
     num_ligne++; //incrémentation du nombre de lignes
     predicat=0; // compteur des predicats
     num_types=0;
     num_champs=0;
     };

return 0;}