// Ce fichier contient les implémentations des classes ChiffrementCesar et ChiffrementSubstitution
// utilisées pour effectuer des opérations de chiffrement et de déchiffrement de messages.

#include "header/Chiffrement.hpp"

// Constructeur de la classe ChiffrementCesar
ChiffrementCesar::ChiffrementCesar(int decalage) : decalage(decalage) {}

// Méthode pour chiffrer un message en utilisant le chiffrement César
string ChiffrementCesar::chiffrer(const string& message) const {
    string resultat = message;
    for (char& c : resultat) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a'; // Détermine la base pour les majuscules ou les minuscules
            c = (c - base + decalage) % 26 + base; // Applique le décalage en gardant les lettres dans l'alphabet
        }
    }
    return resultat;
}

// Méthode pour déchiffrer un texte chiffré en utilisant le chiffrement César
string ChiffrementCesar::dechiffrer(const string& texteChiffre) const {
    string resultat = texteChiffre;
    for (char& c : resultat) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a'; // Détermine la base pour les majuscules ou les minuscules
            c = (c - base - decalage + 26) % 26 + base; // Utilisation de +26 pour gérer les décalages négatifs
        }
    }
    return resultat;
}

// Implémentation de la classe ChiffrementSubstitution

// Constructeur de la classe ChiffrementSubstitution
ChiffrementSubstitution::ChiffrementSubstitution(const string& cle) : cle(cle) {}

// Méthode pour chiffrer un message en utilisant le chiffrement par substitution
string ChiffrementSubstitution::chiffrer(const string& message) const {
    string resultat = message;
    for (char& c : resultat) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a'; // Détermine la base pour les majuscules ou les minuscules
            c = cle[c - base]; // Remplace chaque lettre par sa correspondante dans la clé
        }
    }
    return resultat;
}

// Méthode pour déchiffrer un texte chiffré en utilisant le chiffrement par substitution
string ChiffrementSubstitution::dechiffrer(const string& texteChiffre) const {
    string resultat = texteChiffre;
    for (char& c : resultat) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a'; // Détermine la base pour les majuscules ou les minuscules
            c = find(cle.begin(), cle.end(), c) - cle.begin() + base; // Retrouve la lettre d'origine dans la clé
        }
    }
    return resultat;
}
