#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

void affichage(){
    char reponse='0';
    while(1) {
        printf("                                               ||Bienvenue sur Hospilib||\n");
        printf("                                             ||Que souhaiter vous faire ?||\n");
        printf("1 : Prendre une rendez-vous\n2 : Supprimer un rendez-vous\n3 : Voir ses rendez-vous\n4 : Quitter l'application\n");
        scanf(" %c",&reponse);
        getchar();

        switch(reponse){
            case '1' :
                ajout_RDV();
                break;
            case '2' :
                suppression_RDV();
                break;
            case '3' :
                voir_RDV();
                break;
            case '4' :
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
