#include <mysql/mysql.h>
#include <stdio.h>

int ajout_Patient(char prenom[60], char nom[60]){
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        
        char *server = "localhost";
        char *user = "root";
        char *password = "";
        char *database = "hopital";

        conn = mysql_init(NULL);

        /* Connect to database */
        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
                exit(1);
        }

        char query[500];

        sprintf(query, "INSERT INTO Patient (Nom, Prénom) VALUES ('%s','%s')", nom, prenom);

        if (mysql_query(conn, query)) {
                exit(1);
        }
        

        sprintf(query, "SELECT ID_Patient FROM Patient WHERE Nom = '%s' AND Prénom = '%s' ORDER BY ID_Patient DESC LIMIT 1", nom, prenom);

        if (mysql_query(conn, query)) {
                exit(1);
        }

        res = mysql_use_result(conn);

        row = mysql_fetch_row(res);

        int ID_Patient = atoi(row[0]);

        mysql_close(conn);

        return ID_Patient;
}

void supp_Patient(int id_patient) {
    MYSQL *conn;

    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "hopital";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[500];
    sprintf(query, "DELETE FROM Patient WHERE id_patient = '%i'", id_patient);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    mysql_close(conn);
}

void etat_site() {
    MYSQL *conn;

    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "hopital";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[800];
    sprintf(query, "SELECT s.ID_Site, COUNT(r.ID_Patient) AS 'Nombre de patient sur le site' FROM Site s JOIN Lit l ON s.ID_Site=l.ID_Site JOIN RendezVous r ON l.ID_Lit = r.ID_Lit GROUP BY s.ID_Site, s.Nom;");

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("     Site numéro %s\n Nombre de patients sur le site: %s\n", row[0], row[1]);
    }

    mysql_free_result(result);
    mysql_close(conn);
}

void nombrelit(){
        MYSQL *conn;

    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "hopital";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[800];
    sprintf(query, "SELECT Site.ID_Site, COUNT(DISTINCT Lit.ID_Lit) AS 'Nombre de lits sur le site', COUNT(DISTINCT CASE WHEN RendezVous.RendezVousID IS NULL THEN Lit.ID_Lit END) AS 'Nombre de lits vides sur le site' FROM  Site LEFT JOIN Lit ON Site.ID_Site = Lit.ID_Site LEFT JOIN RendezVous ON Lit.ID_Lit = RendezVous.ID_Lit GROUP BY Site.ID_Site, Site.Nom;");

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("     Site numéro: %s\n Nombre de lit sur le site: %s, Nombre de lit vide sur le site: %s\n", row[0], row[1],row[2]);
    }

    mysql_free_result(result);
    mysql_close(conn);
}

void nombre1() {
    MYSQL *conn;

    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "hopital";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[800];
    sprintf(query, "SELECT Patient.Nom, Patient.Prénom FROM Patient JOIN RendezVous ON Patient.ID_Patient = RendezVous.ID_Patient JOIN Lit ON RendezVous.ID_Lit = Lit.ID_Lit JOIN Site ON Lit.ID_Site = Site.ID_Site WHERE Site.ID_Site = 1;");

    printf("     Sur le site 1 :\n");

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("Nom: %s, Prénom: %s\n", row[0], row[1]);
    }

    mysql_free_result(result);
    mysql_close(conn);
}

void nombre2() {
    MYSQL *conn;

    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "hopital";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[800];
    sprintf(query, "SELECT Patient.Nom, Patient.Prénom FROM Patient JOIN RendezVous ON Patient.ID_Patient = RendezVous.ID_Patient JOIN Lit ON RendezVous.ID_Lit = Lit.ID_Lit JOIN Site ON Lit.ID_Site = Site.ID_Site WHERE Site.ID_Site = 2;");

    printf("     Sur le site 2 :\n");

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("Nom: %s, Prénom: %s\n", row[0], row[1]);
    }

    mysql_free_result(result);
    mysql_close(conn);
}

void nombre3() {
    MYSQL *conn;

    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "hopital";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[800];
    sprintf(query, "SELECT Patient.Nom, Patient.Prénom FROM Patient JOIN RendezVous ON Patient.ID_Patient = RendezVous.ID_Patient JOIN Lit ON RendezVous.ID_Lit = Lit.ID_Lit JOIN Site ON Lit.ID_Site = Site.ID_Site WHERE Site.ID_Site = 3;");

    printf("     Sur le site 3 :\n");

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("Nom: %s, Prénom: %s\n", row[0], row[1]);
    }

    mysql_free_result(result);
    mysql_close(conn);
}

void deplacement_patient(char nom[60], char prenom[60], int id, int id_site){
    MYSQL *conn;

    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "hopital";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[500];
    sprintf(query, "UPDATE RendezVous JOIN Patient ON RendezVous.ID_Patient = Patient.ID_Patient JOIN Lit ON RendezVous.ID_Lit = Lit.ID_Lit SET Lit.ID_Site = '%'i' WHERE Patient.Nom = '%s' AND Patient.Prénom = '%s' AND RendezVous.ID_Patient = '%i';", id_site,nom,prenom,id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }  
    mysql_close(conn);
}

int litajout(char type[60], int id_site){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "hopital";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[500];
    sprintf(query, "INSERT INTO Lit (Type_Chambre, ID_Site) VALUES ('%s','%i');", type, id_site);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }  
    
    sprintf(query, "SELECT ID_Lit FROM Lit WHERE Type_Chambre = '%s' AND ID_Site = '%i' ORDER BY ID_Lit DESC LIMIT 1", type, id_site);

    if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);

    int ID_litadj = atoi(row[0]);

    mysql_close(conn);

    return ID_litadj;
}

int litajout2(char type[60], int litadj, int id_site){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "hopital";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[500];
    sprintf(query, "INSERT INTO Lit (Type_Chambre, ID_Lit_Adjacent, ID_Site) VALUES ('%s','%i','%i');", type, litadj, id_site);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }  
    
    sprintf(query, "SELECT ID_Lit FROM Lit WHERE Type_Chambre = '%s' AND ID_Site = '%i' ORDER BY ID_Lit DESC LIMIT 1", type, id_site);

    if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);

    int ID_litadj = atoi(row[0]);

    mysql_close(conn);

    return ID_litadj;
}

void litmodife(int id1, int id2){
    MYSQL *conn;
    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "hopital";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[500];
    sprintf(query, "UPDATE Lit SET ID_Lit_Adjacent = '%i' WHERE ID_Lit = '%i';", id2, id1);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }  

    mysql_close(conn);
}

void litsupp(char type[60], int id){
    MYSQL *conn;
    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "hopital";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[500];

    sprintf(query, "DELETE FROM Lit WHERE Type_Chambre = '%s' AND NOT EXISTS (SELECT 1 FROM RendezVous WHERE RendezVous.ID_Lit = Lit.ID_Lit) AND Lit.ID_Site = '%i';", type, id);

    if (mysql_query(conn, query)) {
        exit(1);
    }  

    mysql_close(conn);
}