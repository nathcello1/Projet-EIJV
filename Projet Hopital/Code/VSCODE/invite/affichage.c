#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

void affichage(){
    char reponse='0';
    while(1) {
        printf("                                               ||Bienvenue sur Hospilib||\n");
        printf("                                             ||Que souhaiter vous faire ?||\n");
        printf("1 : Ajouter un utilisateur\n2 : Quitter l'application\n");
        scanf(" %c",&reponse);
        getchar();

        switch(reponse){
            case '1' :
                ajout();
                break;
            case '2' :
                system("clear");
                printf("Au revoir\n");
                return;
            default :
                system("clear");
                printf("erreur de saisie appuyer sur entrée\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}
