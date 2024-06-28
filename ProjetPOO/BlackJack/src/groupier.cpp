#include "header/groupier.hpp"
#include <cstdlib> // pour rand() et srand()
#include <ctime>   // pour time()

Groupier::Groupier() : Joueur()
{
    this->nom = 'G';
    srand(time(0));
}

void Groupier::distribuer_cartes(Joueur &joueur, int nombre_de_cartes)
{
    for (int i = 0; i < nombre_de_cartes; ++i)
    {
        int choix = rand() % 13 + 1; // Choisi aleatoirement un nombre entre 1 et 13
        char symbole;

        switch (choix) // En fonction du choix, on utilise le symbole correspondant
        {
        case 1:
            symbole = 'A';
            if (joueur.get_score() + 11 <= 21)
            {
                choix = 11;
            }
            else
            {
                choix = 1;
            }
            break;
        case 10:
            symbole = 'X';
            break;
        case 11: // Pour les choix suivants la valeur restera 10
            symbole = 'V';
            choix = 10;
            break;
        case 12:
            symbole = 'Q';
            choix = 10;
            break;
        case 13:
            symbole = 'K';
            choix = 10;
            break;
        default:
            symbole = '0' + choix;
        }

        Carte nouvelle_carte(choix, symbole); // On genere la carte correspondante
        joueur.ajouter_carte(nouvelle_carte); // On l'ajoute au joueur

        // Afficher le message si c'est le joueur qui tire la carte
        if (joueur.get_nom() != 'G')
        {
            cout << "Vous avez tire un " << symbole << "." << endl;
        }
    }
}
