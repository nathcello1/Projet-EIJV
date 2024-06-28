#include <stdio.h>
#include <stdlib.h>

void affichage(){
    char reponse;
    while(1) {
        printf("                                               ||Bienvenue sur Hospilib||\n");
        printf("                                             ||Que souhaiter vous faire ?||\n");
        printf("1 : Consulter l'etat des sites\n2 : Consulter les patients actuellement sur les sites\n3 : Ajouter un utilisateur au personnel de l'hopital\n4 : Supprimer un utilisateur du personnel de l'hopital\n5 : Ajouter des chambres sur un site\n6 : Supprimer des chambres sur un site\n7 : Ajouter un patient sur un site\n8 : Supprimer un patient sur un site\n9 : Deplacer un patient d'un site vers un autre\n0 : Quitter l'application\n");
        scanf(" %c",&reponse);
        getchar();

        switch(reponse){
            case '1' :
                site();   
                break;
            case '2' :
                nombre_patient();
                break;
            case '3':
                ajoutemploye();
                break;
            case '4':
                suppressionemploye();
                break;
            case '5':
                ajoutlit();
                break;
            case '6':
                supplit();
                break;
            case '7':
                ajoutpatient();
                break;
            case '8':
                suppressionpatient();
                break;
            case '9':
                deplacement();
                break;
            case '0' :
                system("clear");
                printf("Au revoir\n");
                return;
            default :
                system("clear");
                printf("erreur de saisie\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}