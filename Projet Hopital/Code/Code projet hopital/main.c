#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check(char a_tester[50]){
   if (strchr(a_tester, ' ') != NULL || strchr(a_tester, ';') != NULL) {
        system("clear");
        printf("Erreur: Il est interdit d'utiliser d'espace ou de point-virgule.\n");
        return;
    }
}

void ajout(){
    system("clear");
    int cr;
    char username[50];
    char mdp[50];
    char command[60];

    printf("Entrer le nom d'utilisateur a ajouter : ");
    fgets(username, sizeof(username), stdin);
    printf("\n");
    printf("Entrer le mot de passe de l'utilisateur a ajouter :");
    fgets(mdp, sizeof(mdp), stdin);

    username[strcspn(username, "\n")] = 0;
    mdp[strcspn(mdp, "\n")] = 0;

    if(check(username) == -1 || check(mdp)==-1){
        return;
    }

    sprintf(command, "sudo useradd %s", username);

    cr=system(command);

    system("clear");

    if (cr != 0) {
        fprintf(stderr, "Impossible d'ajouter l'utilisateur %s\n", username);
    }
    else if (cr == 0){
        printf("Utilisateur %s ajoute avec succes\n", username);
    }
}

void suppression(){
    system("clear");

    char username[50];
    char command[60];

    printf("Entrez le nom de l'utilisateur a supprimer : ");
    fgets(username, sizeof(username), stdin);

    username[strcspn(username, "\n")] = 0;

    if (strchr(username, ' ') != NULL || strchr(username, ';') != NULL) {
        system("clear");
        printf("Erreur: Le nom d'utilisateur ne doit pas contenir d'espace ou de point-virgule.\n");
        return ;
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

void affichage(){
    char reponse='0';
    while(1) {
        printf("                                               ||Bienvenue sur Hospilib||\n");
        printf("                                             ||Que souhaiter vous faire ?||\n");
        printf("1 : Ajouter un utilisateur\n2 : Supprimer un utilisateur\n3 : Quitter l'application\n");
        scanf(" %c",&reponse);
        getchar();

        switch(reponse){
        case '1' :
            ajout();
            break;
        case '2' :
            suppression();
            break;
        case '3' :
            system("clear");
            printf("Au revoir\n");
            return;
        default :
            system("clear");
            printf("erreur de saisie \n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

int main() {
    affichage();
    return 0;
}
