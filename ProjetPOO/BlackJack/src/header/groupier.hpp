#ifndef GROUPIER_HPP
#define GROUPIER_HPP

#include <cstdlib>
#include <ctime>
#include "joueur.hpp"
#include "carte.hpp"
#include <vector>

// Classe groupier permettant de gerer la distribution des cartes au joueur
class Groupier : public Joueur
{
public:
    Groupier();
    void distribuer_cartes(Joueur &joueur, int nombre_de_cartes); // Methode permettant de distribuer les cartes à un joueur
};

#endif
