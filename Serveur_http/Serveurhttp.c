#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <syslog.h>
#include <time.h>

#define BUFFER_SIZE 1024          // Taille du buffer
#define CONFIG_FILE "60.conf" // Nom du fichier de configuration
#define LOG_FILE "server.log"     // Nom du fichier de log

char DocumentRoot[BUFFER_SIZE];
int PORT;

// Fonction de lecture du fichier de configuration
void lecture_ficher_config(const char *nomFichier)
{
    FILE *file = fopen(nomFichier, "r"); // Ouvre le fichier en lecture
    if (file == NULL)
    {
        perror("fopen");
        exit(1);
    }

    char line[BUFFER_SIZE];
    while (fgets(line, sizeof(line), file)) // On lis chaque ligne
    {
        if (strncmp(line, "DocumentRoot=", 13) == 0) // Si la ligne commence par "DocumentRoot="
        {
            strcpy(DocumentRoot, line + 13);               // On copie le chemin du DocumentRoot dans DocumentRoot
            DocumentRoot[strcspn(DocumentRoot, "\n")] = 0; // On supprime le \n à la fin du chemin
        }
        else if (strncmp(line, "Port=", 5) == 0) // Si la ligne commence par "Port="
        {
            PORT = atoi(line + 5); // On copie le numéro de port dans PORT
        }
    }

    fclose(file); // On ferme le fichier
}

// Fonction d'ecriture dans les logs ici en cas d'erreur
void Message_Log_Erreur(const char *message)
{
    openlog("HTTPServer", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_ERR, "Message urgent %s", message);
    closelog();
}

// Fonction d'ecriture dans le fichier server.log
void Message_Log_Connection(int client_socket, const char *Chemin_Fichier)
{
    FILE *log_file = fopen(LOG_FILE, "a"); // On ouvre le fichier de log en mode append
    if (log_file == NULL)
    {
        perror("fopen");
        return;
    }
    struct sockaddr_in addr; // On recupere l'adresse IP du client
    socklen_t addr_len = sizeof(addr);
    getpeername(client_socket, (struct sockaddr *)&addr, &addr_len);
    char *client_ip = inet_ntoa(addr.sin_addr);

    time_t now = time(NULL); // On recupere la date et l'heure actuelles
    struct tm *tm_info = localtime(&now);
    char time_str[32];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(log_file, "%s-%s-%s\n", time_str, client_ip, Chemin_Fichier); // On ecrit la trace de la requête dans le fichier de log

    fclose(log_file); // Fermeture du fichier de log
}

// Fonction de traitement de la requête HTTP
void Requette_http(int client_socket)
{
    char buffer[BUFFER_SIZE];
    int Lecture;

    Lecture = read(client_socket, buffer, BUFFER_SIZE - 1); // Lecture la requête du client

    if (Lecture < 0)
    {
        perror("read");
        close(client_socket);
        return;
    }

    buffer[Lecture] = '\0';

    char Chemin_Fichier[BUFFER_SIZE]; // On analyse la requête HTTP pour obtenir le chemin du fichier demandé
    sscanf(buffer, "GET %s", Chemin_Fichier);

    if (strcmp(Chemin_Fichier, "/") == 0) // Si aucun chemin n'est spécifié, on renvoie sur la page "index.html"
    {
        snprintf(Chemin_Fichier, sizeof(Chemin_Fichier), "/index.html");
    }

    char Chemin_Complet[BUFFER_SIZE]; // Construction du chemin complet du fichier demandé
    snprintf(Chemin_Complet, sizeof(Chemin_Complet), "%s%s", DocumentRoot, Chemin_Fichier);

    Message_Log_Connection(client_socket, Chemin_Complet); // On écrit dans le fichier de log l'adresse ip et le chemin du fichier demandé

    int fichier = open(Chemin_Complet, O_RDONLY); // On ouvre le fichier demandé
    if (fichier < 0)                              // Si le fichier demandé n'existe pas, on envoie une réponse 404 et on écrit dans les logs une erreur
    {
        const char *error_404 =
            "HTTP/1.0 404 Not Found\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 100\r\n"
            "\r\n"
            "<html><body><h1>404 Not Found</h1><p>Le fichier demande n'a pu etre trouve</p></body></html>";
        write(client_socket, error_404, strlen(error_404));
        close(client_socket);
        Message_Log_Erreur("Page 404 - Le fichier demande n'a pu etre trouve");
        return;
    }
    const char *Type_Fichier; // On détermine le type de contenu en fonction de l'extension du fichier
    if (strstr(Chemin_Complet, ".html") != NULL)
    {
        Type_Fichier = "text/html";
    }
    else if (strstr(Chemin_Complet, ".css") != NULL)
    {
        Type_Fichier = "text/css";
    }
    else if (strstr(Chemin_Complet, ".png") != NULL)
    {
        Type_Fichier = "image/png";
    }
    else if (strstr(Chemin_Complet, ".jpg") != NULL)
    {
        Type_Fichier = "image/jpeg";
    }

    struct stat Fichier_contenu; // Le contenu du fichier est lu et transmit au client
    fstat(fichier, &Fichier_contenu);
    char Fichier_trouve[BUFFER_SIZE];
    snprintf(Fichier_trouve, sizeof(Fichier_trouve),
             "HTTP/1.0 200 OK\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %ld\r\n"
             "\r\n",
             Type_Fichier, Fichier_contenu.st_size);
    write(client_socket, Fichier_trouve, strlen(Fichier_trouve));
    sendfile(client_socket, fichier, NULL, Fichier_contenu.st_size);

    close(fichier); // On ferme le fichier et le socket client
    close(client_socket);
}

// Fonction de traitement de la morte des fils
void signal_enfant_meurt(int sig)
{
    while (waitpid(-1, NULL, WNOHANG) > 0) // Attend tous les processus zombies
        ;
}

int main()
{
    lecture_ficher_config(CONFIG_FILE);

    if (fork() != 0) // Transforme en Daemon
    {
        exit(0);
    }
    setsid();
    lecture_ficher_config(CONFIG_FILE); // On relie le fichier de config apres la creation du Daemon

    Message_Log_Erreur("Le serveur est lance"); // On confirme dans les logs que le serveur c'est bien lancé

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    signal(SIGCHLD, signal_enfant_meurt); // On traite la mort des fils

    server_socket = socket(AF_INET, SOCK_STREAM, 0); // On crée le socket serveur
    if (server_socket < 0)
    {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) // Si le serveur ne peut pas se lier au port, on affiche un message d'erreur et on ferme le serveur
    {
        perror("bind");
        close(server_socket);
        exit(1);
    }

    if (listen(server_socket, 10) < 0) // Si le serveur ne peut pas écouter les connexions, on affiche un message d'erreur et on ferme le serveur
    {
        perror("listen");
        close(server_socket);
        exit(1);
    }

    while (1)
    {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len); // On accepte une connexion
        if (client_socket < 0)                                                                    // Si le serveur ne peut pas accepter la connexion, on affiche un message d'erreur et on ferme le serveur
        {
            perror("accept");
            close(server_socket);
            exit(1);
        }

        pid_t pid = fork();
        if (pid < 0) // Si le serveur ne peut pas créer un fils, on affiche un message d'erreur et on ferme le serveur
        {
            perror("fork");
            close(client_socket);
            close(server_socket);
            exit(1);
        }
        else if (pid == 0) // Si le serveur a créé un fils, on ferme le socket client et on traite la requête http
        {
            close(server_socket);
            Requette_http(client_socket);
            exit(0);
        }
        else // Si le serveur n'a pas créé de fils, on ferme le socket client
        {
            close(client_socket);
        }
    }

    close(server_socket);

    return 0;
}