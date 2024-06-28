#ifndef REGLE_HPP
#define REGLE_HPP

#include <iostream>
#include "joueur.hpp"
#include "groupier.hpp"
#include "jeu.hpp"

// Classe Regle permettant de gerer les regles du jeu
class Regle : public Joueur, public Groupier
{
public:
    void joueur_bust(Joueur &joueur, Groupier &groupier);                        // Methode permettant de verifier et de gerer le cas ou le joueur bust
    void tour_groupier(Groupier &groupier, Joueur &joueur);                      // Methode permettant de gerer le tour du groupier
    void groupier_bust(Groupier &groupier, Joueur &joueur);                      // Methode permettant de verifier et de gerer le cas ou le groupier bust
    void Gagnant(Joueur &joueur, Groupier &groupier);                            // Methode permettant de verifier et de gerer si le joueur a gagné, perdu ou si la partie est une égalite
    void rejouer(Joueur &joueur, Groupier &groupier);                            // Methode permettant de gerer le cas ou le joueur veut rejouer
    void main1gagnant(Joueur &joueur, Groupier &groupier);                       // Methode permettant de verifier et de gerer le cas ou le joueur a gagné ou perdu avec la main 1
    void main2gagnant(Joueur &joueur, Groupier &groupier, Joueur &joueur_split); // Methode permettant de verifier et de gerer le cas ou le joueur a gagné ou perdu avec la main 2
    void misevalable(Joueur &joueur);                                            // Methode permettant de verifier si le joueur a entré une mise rentrant dans les regles de mise (entre 5 et 300)
};

#endif