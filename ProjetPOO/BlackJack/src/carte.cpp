#include "header/carte.hpp"

Carte::Carte(int valeur, char symbole) : valeur(valeur), symbole(symbole) {}

int Carte::get_valeur() const
{
    return valeur;
}

char Carte::get_symbole() const
{
    return symbole;
}

int Carte::set_valeur(int valeur)
{
    this->valeur = valeur;
    return valeur;
}

void Carte::afficher() const
{
    cout << symbole << " sa valeur vaut : " << valeur << endl;
}

As::As() : Carte(11, 'A') {}

Deux::Deux() : Carte(2, '2') {}

Trois::Trois() : Carte(3, '3') {}

Quatre::Quatre() : Carte(4, '4') {}

Cinq::Cinq() : Carte(5, '5') {}

Six::Six() : Carte(6, '6') {}

Sept::Sept() : Carte(7, '7') {}

Huit::Huit() : Carte(8, '8') {}

Neuf::Neuf() : Carte(9, '9') {}

Dix::Dix() : Carte(10, 'X') {}

Valet::Valet() : Carte(10, 'V') {}

Reine::Reine() : Carte(10, 'Q') {}

Roi::Roi() : Carte(10, 'K') {}