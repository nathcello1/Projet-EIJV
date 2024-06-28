#ifndef JEU_HPP
#define JEU_HPP

#include <iostream>
#include "joueur.hpp"
#include "groupier.hpp"
#include "regle.hpp"

// Classe Jeu permettant de generer et de gérer le deroulement de la partie
class Jeu
{
public:
    void deroulement_partie(Joueur &joueur, Groupier &groupier);                      // Methode permettant de gérer le deroulement de la partie
    void deroulement_split(Joueur &joueur, Joueur &joueur_split, Groupier &groupier); // Methode permettant de gérer le deroulement de la partie apres un split
    void initialisation();                                                            // Methode permettant d'initialiser une partie
};

#endif