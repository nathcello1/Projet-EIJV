#ifndef SQL_H
#define SQL_H

void connexion();
int ajout_Patient(char prenom[60], char nom[60]);
void supp_Patient(int id_patient);
void etat_site();
void nombre1();
void nombre2();
void nombre3();
void nombrelit();
void deplacement_patient(char nom[60], char prenom[60], int id, int id_site);
int litajout(char type[60], int id_site);
int litajout2(char type[60], int litadj, int id_site);
void litmodife(int id1, int id2);
void litsupp(char type[60], int id);
#endif