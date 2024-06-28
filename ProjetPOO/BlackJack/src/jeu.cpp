#include "header/jeu.hpp"

void Jeu::initialisation()
{ // Creation du joueur et du groupier
    system("cls");
    cout << "Bienvenue dans le jeu de Blackjack!" << endl;
    Joueur joueur;
    Groupier groupier;
    deroulement_partie(joueur, groupier); // Lancement du deroulement de la partie
}

void Jeu::deroulement_partie(Joueur &joueur, Groupier &groupier)
{
    Regle regle;
    int choix;

    while (true)
    {
        regle.misevalable(joueur); // Demande de la mise du joueur

        // Réinitialisation des mains du joueur et du groupier
        joueur.vider_main();
        groupier.vider_main();

        // Distribution de cartes
        groupier.distribuer_cartes(joueur, 2);   // Distribue 2 cartes au joueur
        groupier.distribuer_cartes(groupier, 2); // Distribue 2 cartes au groupier

        cout << endl;

        // Affichage des cartes du joueur
        cout << "Main du joueur : " << endl;
        joueur.afficher_main();
        cout << "Score du joueur : " << joueur.get_score() << "\n"
             << endl;

        // Affichage d'un carte du groupier
        cout << "Main du groupier : " << endl;
        groupier.afficher_main_groupier();
        cout << endl;

        while (true)
        {
            // Tour du joueur
            cout << "Que souhaitez-vous faire ? (1/2/3/4/5)" << endl;
            cout << "1 - tirer une carte" << endl;
            cout << "2 - Rester" << endl;
            cout << "3 - Doubler votre mise" << endl;
            cout << "4 - Split votre jeu" << endl;
            cout << "5 - Afficher votre main votre score et la carte visible du groupier " << endl;
            cout << "Votre choix : ";
            cin >> choix;

            switch (choix)
            {
            case 1:
                system("cls");
                groupier.distribuer_cartes(joueur, 1); // Distribue 1 carte au joueur
                cout << endl
                     << "Nouvelle main du joueur : " << endl;
                joueur.afficher_main();
                cout << "Nouveau score du joueur : " << joueur.get_score() << endl
                     << endl;
                regle.joueur_bust(joueur, groupier); // On verifie si le joueur a bust
                break;
            case 2:
                system("cls");
                cout << "Vous avez decide de rester." << endl;
                break;
            case 3:
                system("cls");
                cout << "Vous avez decide de doubler votre mise" << endl;
                joueur.set_mise(joueur.get_mise() * 2); // On double la mise
                cout << "Votre mise est maintenant de " << joueur.get_mise() << endl;
                groupier.distribuer_cartes(joueur, 1); // Et on distribue 1 carte au joueur puis on fini son tour
                cout << endl
                     << "Nouvelle main du joueur : " << endl;
                joueur.afficher_main();
                cout << "Nouveau score du joueur : " << joueur.get_score() << endl;
                regle.joueur_bust(joueur, groupier);
                break;
            case 4:
                system("cls");
                if (joueur.peut_split()) // On verifie si le joueur peut split
                {
                    cout << "Vous avez split votre main." << endl;
                    Joueur new_joueur = joueur.split();              // On split la main du joueur en creant un nouveau joueur avec comme valeur une carte de la meme valeur que la main de départ et la meme mise
                    deroulement_split(joueur, new_joueur, groupier); // On lance le deroulement du jeu avec comme regle que le joueur a split sa main
                }
                else
                {
                    cout << "Vous ne pouvez pas split cette main." << endl;
                    continue;
                }
                break;
            case 5:
                // Affichage des informations du joueur et d'une carte du groupier
                system("cls");
                cout
                    << "Main du joueur : " << endl;
                joueur.afficher_main();
                cout << "Score du joueur : " << joueur.get_score() << "\n"
                     << endl;
                cout << "Mise du joueur : " << joueur.get_mise() << "\n"
                     << endl;
                // Affichage des cartes du groupier
                cout << "Main du groupier : " << endl;
                groupier.afficher_main_groupier();
                cout << endl;
                continue;
            default:
                system("cls");
                cout << "Choix invalide. Veuillez choisir une option valide." << endl;
                continue;
            }

            // Si le choix fais est 2, 3 ou 4 alors on fini le tour du joueur et on sort du switch
            if (choix == 2 || choix == 3 || choix == 4)
            {
                break;
            }
        }

        cout << endl;
        // Tour du groupier
        regle.tour_groupier(groupier, joueur);

        // Comparaison des scores pour determiner le gagnant
        regle.Gagnant(joueur, groupier);
    }
}

// Deroulement d'une partie si le joueur a split sa main
void Jeu::deroulement_split(Joueur &joueur, Joueur &joueur_split, Groupier &groupier)
{
    Regle regle;

    cout << endl;
    cout << "Votre premiere main : " << endl;
    joueur.afficher_main();
    cout << "Score de la main 1 : " << joueur.get_score() << endl
         << endl;
    cout << "Mise sur la main 1 : " << joueur.get_mise() << endl
         << endl;
    cout << "Votre deuxieme main : " << endl;
    joueur_split.afficher_main();
    cout << "Score de la main 2 : " << joueur_split.get_score() << endl
         << endl;
    cout << "Mise sur la main 2 : " << joueur_split.get_mise() << endl
         << endl;

    while (true)
    {
        cout << "Que voulez-vous faire? (1/2/3)" << endl;
        cout << "1 - Tirer une carte" << endl;
        cout << "2 - Rester" << endl;
        cout << "3 - Afficher vos mains et celle du groupier" << endl;
        cout << "Votre choix : ";
        int choix;
        cin >> choix;

        switch (choix)
        {
        case 1:
            system("cls");
            cout << "Voulez-vous tirer une carte sur votre premiere ou deuxieme main ? (1/2)" << endl;
            int choix_split;
            cin >> choix_split;
            // Dans le cas ou le joueur a split sa main alors il peut tirer une carte sur sa main 1 ou 2
            if (choix_split == 1)
            {
                system("cls");
                groupier.distribuer_cartes(joueur, 1);
                cout << "Nouvelle main 1 : " << endl;
                joueur.afficher_main();
                cout << "Score de la main 1 : " << joueur.get_score() << endl
                     << endl;
            }
            else if (choix_split == 2)
            {
                system("cls");
                groupier.distribuer_cartes(joueur_split, 1);
                cout << "Nouvelle main 2 : " << endl;
                joueur_split.afficher_main();
                cout << "Score de la main 2 : " << joueur_split.get_score() << endl
                     << endl;
            }
            break;

        case 2:
            system("cls");
            cout << "Vous restez sur vos deux mains." << endl;
            break;

        case 3:
            system("cls");
            cout << "Votre main 1 : " << endl;
            joueur.afficher_main();
            cout << "Votre main 2 : " << endl;
            joueur_split.afficher_main();
            cout << endl;
            cout << "Score de la main 1 : " << joueur.get_score() << endl;
            cout << "Score de la main 2 : " << joueur_split.get_score() << endl;
            cout << endl;
            cout << "Main du groupier : " << endl;
            groupier.afficher_main_groupier();
            cout << endl;
            continue;

        default:
            system("cls");
            cout << "Choix invalide. Veuillez choisir une option valide." << endl;
            continue;
        }

        if (choix == 2)
        {
            break;
        }
    }

    system("cls");
    // Tour du groupier
    regle.tour_groupier(groupier, joueur);

    // Comparaison des scores pour déterminer le gagnant
    regle.main1gagnant(joueur, groupier);
    regle.main2gagnant(joueur_split, groupier, joueur);

    cout << "Vos gains sont maintenant de " << joueur.get_mise_depart() << endl;
    regle.rejouer(joueur, groupier); // Propose au joueur de rejouer ou non
}