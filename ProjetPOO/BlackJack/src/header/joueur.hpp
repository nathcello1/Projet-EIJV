#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include "carte.hpp"
#include <vector>

// Classe Joueur permettant les différentes actions possible du joueur
class Joueur
{
protected:
    vector<Carte> mains[2]; // Permet de stocker les cartes de la main du joueur (2 car si il y a split alors on jouera avec 2 mains)
    int scores[2];          // Score du joueur (2 car si il y a split alors on jouera avec 2 mains)
    char nom;               // Nom du joueur
    int main_index;         // Permet de savoir sur quel index on doit jouer (0 ou 1) et donc sur quelle main jouer
    int mise;               // Mise du joueur
    int mise_depart;        // Mise du joueur au depart du jeu (on peut aussi l'appeler gain du joueur)

public:
    Joueur();
    void ajouter_carte(const Carte &carte);            // Methode permettant d'ajouter une carte choisi à la main du joueur
    void ajouter_carte(const Carte &carte, int index); // Methode permettant d'ajouter une carte choisi en choisissant aussi la main dans laquelle l'ajouter
    void afficher_main() const;                        // Methode permettant d'afficher la main du joueur
    void afficher_main(int index) const;               // Methode permettant de choisir la main a afficher
    int get_score() const;                             // Methode permettant de recuperer le score du joueur
    int get_score(int index) const;                    // Methode permettant de recuperer le score du joueur choisi
    void set_score(int score, int index);              // Methode permettant de modifier le score du joueur choisi
    char get_nom() const;                              // Methode permettant de recuperer le nom du joueur
    void afficher_main_groupier() const;               // Methode permettant d'afficher 1 seule carte de la main du groupier
    bool peut_split() const;                           // Methode pour verifier si le joueur peut split sa main
    int get_mise() const;                              // Methode permettant de recuperer la mise du joueur
    void set_mise(int mise);                           // Methode permettant de modifier la mise du joueur
    int get_mise_depart() const;                       // Methode permettant de recuperer la mise de depart du joueur
    void set_mise_depart(int rajout);                  // Methode permettant de modifier la mise de depart du joueur en augmentant celle ci
    void set_mise_departJeu(int perte);                // Methode permettant de modifier la mise de depart du joueur en diminuant celle ci
    void vider_main();                                 // Methode permettant de vider la main du joueur
    Joueur split();                                    // Methode creant un nouveau joueur si je joueur peut split avec la meme mise et un carte avec la meme valeur et le meme symbole que celle retiré au joueur
};

#endif
