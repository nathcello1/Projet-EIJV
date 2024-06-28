#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SQL.h"

int check_System(char a_tester[50]){
    if (strchr(a_tester, ' ') != NULL || strchr(a_tester, ';') != NULL) {
        system("clear");
        printf("Erreur: Il est interdit d'utiliser d'espace ou de point-virgule.\n");
        return -1;
    }
} 

int check_SQL(char a_tester[60]){
    for(int i=0; i<strlen(a_tester)-1; i++){
        if(!((a_tester[i] >= 65 && a_tester[i] <= 90) || (a_tester[i] >= 97 && a_tester[i] <= 122))){
            printf("%d, %d", a_tester[i], i);
            printf("\nUtilisez des lettres de l'alphabet !\n");
            return 0;
        }
    }
    return 1;
} 

void reductionString(char aReduire[60]){
    int i = 0;
    while(aReduire[i] != '\n'){
        printf("%c %d\n", aReduire[i], aReduire[i]);
        i++;
    }
    aReduire[i] = '\0';
}

void ajout(){
    system("clear");
    int cr;
    char username[50];
    char prenom[60];
    char nom[60];
    char command[200];

    printf("Entrez le nom d'utilisateur a ajouter : ");
    fgets(username, sizeof(username), stdin);
    printf("\n");

    username[strcspn(username, "\n")] = 0;
    
    if (check_System(username)==-1)
    {
        return;
    }

    int verification = 0;
    do{
        printf("Entrez votre prénom : ");
        fgets(prenom, sizeof(prenom), stdin);
        ("\n");
        verification = check_SQL(prenom);
    }while(verification == 0);

    verification = 0;
    do{
        printf("Entrez votre nom : ");
        fgets(nom, sizeof(nom), stdin);
        ("\n");
        verification = check_SQL(nom);
    }while(verification == 0);

    reductionString(prenom);
    reductionString(nom);


    int ID_Patient = ajout_Patient(prenom, nom);

    sprintf(command, "sudo useradd -G patient %s", username);

    cr=system(command);

    sprintf(command, "sudo passwd %s", username);

    system("clear");

    system(command);
    
    if (cr != 0) {
        fprintf(stderr, "Impossible d'ajouter l'utilisateur %s\n", username);
    }
    else if (cr == 0){
        printf("Utilisateur %s ajoute avec succes, votre identifiant de patient est le %d, retenez le bien !\n", username, ID_Patient);
    }
}