#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BLOCK_SIZE 1024

int main(int argc, char *argv[]) {
    // Vérification des arguments
    if (argc != 4) {
        fprintf(stderr, "Usage : %s <nom_fichier> <char1> <char2>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char char1 = argv[2][0];
    char char2 = argv[3][0];
    int remplacements = 0;

    // Ouvrir le fichier
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    char buffer[BLOCK_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, BLOCK_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == char1) {
                buffer[i] = char2;
                remplacements++;
            }
        }

        // Repositionner le curseur et écrire le bloc modifié
        if (lseek(fd, -bytes_read, SEEK_CUR) == -1) {
            perror("Erreur lors de l'utilisation de lseek");
            close(fd);
            return 1;
        }

        if (write(fd, buffer, bytes_read) != bytes_read) {
            perror("Erreur lors de l'écriture dans le fichier");
            close(fd);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("Erreur lors de la lecture du fichier");
    }

    // Fermer le fichier
    close(fd);

    // Affichage du résultat
    printf("%d remplacement(s) '%c' -> '%c'\n", remplacements, char1, char2);

    return 0;
}

