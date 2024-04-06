%option noyywrap
%{
	#include<stdio.h>
%}
chiff [0-9]
mat ((({chiff}){1,3})"TUNIS"(({chiff}){1,4}))"#"
%%
{mat} printf(" valide "); 
.* printf("invalide "); 
%%
int main()
{
//On veut concevoir un vérificateur qui vérifie que des chaines saisies peuvent correspondre 
//à une immatriculation de véhicule en Tunisie.  
//On vérifie donc que la chaine saisie commence par 1 ou 2 ou 3 chiffres ensuite la chaine  
//TUNIS ensuite 1 ou 2 ou 3 ou 4 chiffres ensuite le caractère #.  
//Exemple de mots : 160TUNIS9876# 43TUNIS234# 8TUNIS24# 
	yylex();
	return 0;
}