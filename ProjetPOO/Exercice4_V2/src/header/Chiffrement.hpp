#ifndef CHIFFREMENT_HPP
#define CHIFFREMENT_HPP

#include <string>
#include <algorithm> 
using namespace std;

// La classe de base, c'est une classe abstraite car contient des méthodes virtuelles PURES
class Chiffrement {
public:
    virtual string chiffrer(const string& message) const = 0;
    virtual string dechiffrer(const string& texteChiffre) const = 0;
    virtual ~Chiffrement() {}
};

// Classe héritante de Chiffrement
class ChiffrementCesar : public Chiffrement {
private:
    // César fonctionne avec un principe de décalage de lettre de l'alphabet
    int decalage;
public:
    ChiffrementCesar(int decalage);
    virtual string chiffrer(const string& message) const override;
    virtual string dechiffrer(const string& texteChiffre) const override;
};

// Classe 2 héritante de Chiffrement
class ChiffrementSubstitution : public Chiffrement {
private:
    // Fonctionne avec une clé de subtitution de 26 caracères pour retrouver le message encodé
    string cle;
public:
    ChiffrementSubstitution(const string& cle);
    virtual string chiffrer(const string& message) const override;
    virtual string dechiffrer(const string& texteChiffre) const override;
};

#endif