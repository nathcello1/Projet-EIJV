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
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
        }

        char query[500];

        sprintf(query, "INSERT INTO Patient (Nom, Prénom) VALUES ('%s','%s')", nom, prenom);

        if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
        }
        

        sprintf(query, "SELECT ID_Patient FROM Patient WHERE Nom = '%s' AND Prénom = '%s' ORDER BY ID_Patient DESC LIMIT 1", nom, prenom);

        if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
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