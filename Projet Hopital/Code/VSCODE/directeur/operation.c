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

void ajoutpatient(){
    system("clear");
    int cr;
    char username[50];
    char prenom[60];
    char nom[60];
    char command[200];

    printf("Entrez le nom d'utilisateur du patient a ajouter : ");
    fgets(username, sizeof(username), stdin);
    printf("\n");

    username[strcspn(username, "\n")] = 0;
    
    if (check_System(username)==-1)
    {
        return;
    }

    int verification = 0;
    do{
        printf("Entrez son prénom : ");
        fgets(prenom, sizeof(prenom), stdin);
        ("\n");
        verification = check_SQL(prenom);
    }while(verification == 0);

    verification = 0;
    do{
        printf("Entrez son nom : ");
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
        printf("Utilisateur %s ajoute avec succes, son identifiant de patient est le %d, retenez le bien !\n", username, ID_Patient);
    }
}

void suppressionpatient(){
    system("clear");

    char username[50];
    char command[200];
    int id;

    printf("Entrez le nom d'utilisateur du patient a supprimer : ");
    fgets(username, sizeof(username), stdin);

    username[strcspn(username, "\n")] = 0;

    if (check_System(username)==-1)
    {
        return;
    }

    printf("Entrer l'ID du patient a supprimer : ");
    scanf("%i",&id);

    supp_Patient(id);

    sprintf(command, "sudo userdel %s", username);

    int cr = system(command);

    system("clear");

    if (cr != 0) {
        fprintf(stderr, "Impossible de supprimer l'utilisateur %s\n", username);
    }
    else if(cr == 0) {
        printf("Utilisateur %s supprime avec succes\n", username);
    }
}

void site(){
    int i=1;
    system("clear");
    printf("Voici l'etat des sites :\n\n");
    etat_site();
    printf("\n");
    nombrelit();
    printf("\nTaper 0 pour revenir au menu\n");
    while (i!=0)
    {
        scanf("%i",&i);
    }
    system("clear"); 
}

void nombre_patient(){
    int i=1;
    system("clear");
    printf("Voici les patients sur les sites :\n\n");
    nombre1();
    printf("\n");
    nombre2();
    printf("\n");
    nombre3();
    printf("\n");
    printf("Taper 0 pour revenir au menu\n");
    while (i!=0)
    {
        scanf("%i",&i);
    }
    system("clear"); 
}

void ajoutemploye(){
    system("clear");
    int cr;
    char username[50];
    char prenom[60];
    char nom[60];
    char command[200];

    printf("Entrez le nom d'utilisateur de l'employe a ajouter : ");
    fgets(username, sizeof(username), stdin);
    printf("\n");

    username[strcspn(username, "\n")] = 0;
    
    if (check_System(username)==-1)
    {
        return;
    }

    sprintf(command, "sudo useradd -G employe %s", username);

    cr=system(command);

    sprintf(command, "sudo passwd %s", username);

    system("clear");

    system(command);
    
    if (cr != 0) {
        fprintf(stderr, "Impossible d'ajouter l'utilisateur %s\n", username);
    }
    else if (cr == 0){
        printf("Utilisateur %s ajoute avec succes !\n", username);
    }
}

void suppressionemploye(){
    system("clear");

    char username[50];
    char command[200];
    int id;

    printf("Entrez le nom d'utilisateur de l'employe a supprimer : ");
    fgets(username, sizeof(username), stdin);

    username[strcspn(username, "\n")] = 0;

    if (check_System(username)==-1)
    {
        return;
    }

    sprintf(command, "sudo userdel %s", username);

    int cr = system(command);

    system("clear");

    if (cr != 0) {
        fprintf(stderr, "Impossible de supprimer l'utilisateur %s\n", username);
    }
    else if(cr == 0) {
        printf("Utilisateur %s supprime avec succes\n", username);
    }
}

void deplacement(){
    system("clear");
    int id;
    int id_site;
    char prenom[60];
    char nom[60];
    int verification = 0;

    do{
        printf("Entrez le prénom du patient a deplacer : ");
        fgets(prenom, sizeof(prenom), stdin);
        ("\n");
        verification = check_SQL(prenom);
    }while(verification == 0);

    verification = 0;

    do{
        printf("Entrez le nom du patient a deplacer : ");
        fgets(nom, sizeof(nom), stdin);
        ("\n");
        verification = check_SQL(nom);
    }while(verification == 0);

    printf("Entrer l'ID du patient a deplacer : ");
    scanf("%i",&id);

    printf("Vers quel site souhaitez vous le deplacer : ");
    scanf("%i",&id_site);
    
    reductionString(prenom);
    reductionString(nom);

    deplacement_patient(nom,prenom,id,id_site);
    system("clear");
}

void supplit(){
    system("clear");
    char typelit[60];
    int id_site;
    int verification = 0;

    do {
        printf("Quel est le type de lit que vous souhaitez supprimer : ");
        fgets(typelit, sizeof(typelit), stdin);
        ("\n");
        verification = check_SQL(typelit);
    } while (verification == 0);

    reductionString(typelit);

    printf("Sur quel site souhaiter vous supprimer le lit : ");
    scanf("%i",&id_site);

    litsupp(typelit,id_site);
    system("clear");   
}

void ajoutlit() {
    system("clear");
    int idlit1;
    int idlit2;
    int id_site;
    char typelit[60];
    int verification = 0;

    do {
        printf("Quel est le type de lit que vous souhaitez ajouter : ");
        fgets(typelit, sizeof(typelit), stdin);
        ("\n");
        verification = check_SQL(typelit);
    } while (verification == 0);

    reductionString(typelit);

    printf("Sur quel site souhaiter vous ajouter un lit : ");
    scanf("%i",&id_site);

    if (typelit[0] == 'D') {
        idlit1=litajout(typelit,id_site);
        idlit2=litajout2(typelit,idlit1,id_site);
        litmodife(idlit1,idlit2);
    }
    else if (typelit[0] == 'S')
    {
        idlit1=litajout(typelit,id_site);  
    }
    else{
        printf("erreur\n");
    }
    system("clear");
}