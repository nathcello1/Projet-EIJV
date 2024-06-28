#ifndef CARTE_HPP
#define CARTE_HPP

#include <iostream>
using namespace std;

// Classe permettant de definir le symbole et la valeur d'une carte
class Carte
{
protected:
    int valeur;   // Valeur de la carte (1,2,3 etc...)
    char symbole; // Symbole de la carte (A,2,3 etc...)

public:
    Carte(int valeur, char symbole);
    int get_valeur() const;     // Retourne la valeur de la carte
    char get_symbole() const;   // Retourne le symbole de la carte
    int set_valeur(int valeur); // Modifie la valeur de la carte
    void afficher() const;      // Affiche la carte
};

class As : public Carte
{
public:
    As();
};

class Deux : public Carte
{
public:
    Deux();
};

class Trois : public Carte
{
public:
    Trois();
};

class Quatre : public Carte
{
public:
    Quatre();
};

class Cinq : public Carte
{
public:
    Cinq();
};

class Six : public Carte
{
public:
    Six();
};

class Sept : public Carte
{
public:
    Sept();
};

class Huit : public Carte
{
public:
    Huit();
};

class Neuf : public Carte
{
public:
    Neuf();
};

class Dix : public Carte
{
public:
    Dix();
};

class Valet : public Carte
{
public:
    Valet();
};

class Reine : public Carte
{
public:
    Reine();
};

class Roi : public Carte
{
public:
    Roi();
};

#endif