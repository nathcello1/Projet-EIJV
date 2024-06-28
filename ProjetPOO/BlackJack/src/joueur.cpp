#include "header/joueur.hpp"

Joueur::Joueur() : nom('1'), main_index(0)
{
    scores[0] = 0;
    scores[1] = 0;
    mise = 0;
    mise_depart = 100;
}

void Joueur::ajouter_carte(const Carte &carte)
{
    ajouter_carte(carte, main_index);
}

int Joueur::get_mise_depart() const
{
    return mise_depart;
}

void Joueur::set_mise_depart(int rajout)
{
    mise_depart += rajout * 1.5; // Si le joueur gagne alors on ajoute a sa mise 1.5 fois sa mise
}

void Joueur::set_mise_departJeu(int perte)
{
    mise_depart -= perte;
}

void Joueur::ajouter_carte(const Carte &carte, int index)
{
    mains[index].push_back(carte);       // On ajoute a la main correspondant a l'index une carte
    scores[index] += carte.get_valeur(); // On ajoute au score correspondant a l'index la valeur de la carte ajouté
}

void Joueur::afficher_main() const
{
    afficher_main(main_index);
}

void Joueur::afficher_main(int index) const
{
    for (const auto &carte : mains[index]) // On parcours la main a l'index indiqué et on affiche chaque carte
    {
        carte.afficher();
    }
    cout << endl;
}

void Joueur::afficher_main_groupier() const
{
    mains[0].front().afficher(); // On affiche la premiere carte de la main du groupier
}

int Joueur::get_score() const
{
    return get_score(main_index);
}

int Joueur::get_score(int index) const
{
    int score = 0;
    for (const auto &carte : mains[index]) // On ajoute a la variable score la valeur de chaque carte contenu dans la main correpondant a l'index
    {
        int valeur = carte.get_valeur();
        score += valeur;
    }
    return score; // On retourne le score
}

void Joueur::set_score(int score, int index)
{
    scores[index] = score;
}

char Joueur::get_nom() const
{
    return nom;
}

bool Joueur::peut_split() const
{
    return mains[0].size() == 2 && mains[0][0].get_valeur() == mains[0][1].get_valeur(); // Si le joueur a 2 cartes et que les valeurs sont les memes alors il peut split
}

int Joueur::get_mise() const
{
    return mise;
}

void Joueur::set_mise(int mise)
{
    this->mise = mise;
}

void Joueur::vider_main()
{
    for (auto &main : mains)
    {
        main.clear();
    }
    scores[0] = 0;
    scores[1] = 0;
}

Joueur Joueur::split()
{
    Joueur new_joueur;
    new_joueur.ajouter_carte(mains[0].back(), 0); // On ajoute la derniere carte de la main du joueur au nouveau joueur
    mains[0].pop_back();                          // On retire la derniere carte de la main du joueur
    scores[0] = mains[0][0].get_valeur();         // Met à jour le score après le split
    new_joueur.set_mise(mise);                    // Le nouveau joueur a la même mise de départ

    return new_joueur;
}
