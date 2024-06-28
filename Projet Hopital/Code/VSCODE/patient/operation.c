#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void ajout_RDV(){
    printf("\nSelectionnez une spécialité:\n1 : Cardiologie\n2 : Cancerologie\n3 : Podologie\nautre chose : Pour retourner au menu");
    int choixSpecialite;
    scanf(" %d", choixSpecialite);
    if(choixSpecialite == 1 || choixSpecialite == 2 || choixSpecialite == 3){
        printf("Choisissez un type de chambre\n1 : Chambre double \n2 : simple avec un supplément de 5e\nautre chose : Pour retourner au menu");
        int choixTypeChambre;
        scanf(" %d", choixTypeChambre);
        if(choixTypeChambre == 1 || choixTypeChambre == 2){
            LitDisponible();
        } else {
            return;
        }
    } else {
        return;
    }
}