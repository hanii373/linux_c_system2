#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BLOCK_SIZE 1024

int longueurPremiereLigne(int fd) {
    int longueur = 0;
    char c;

    while (read(fd, &c, 1) == 1) {
        if (c == '\n') break;
        longueur++;
    }

    lseek(fd, 0, SEEK_SET);
    return longueur;
}

int estFichierValide(int fd) {
    char c;

    while (read(fd, &c, 1) == 1) {
        if (c != 'v' && c != '>' && c != '\n') {
            lseek(fd, 0, SEEK_SET);
            return 0; // Fichier invalide
        }
    }

    lseek(fd, 0, SEEK_SET);
    return 1; // Fichier valide
}

void remplacerEtSuivreFleches(int fd, char char1, char char2) {
    int ligne = 0, colonne = 0;
    int remplacements = 0;
    int longueurLigne = longueurPremiereLigne(fd);
    char c;

    while (read(fd, &c, 1) == 1) {
        if (c == char1) {
            lseek(fd, -1, SEEK_CUR);
            write(fd, &char2, 1);
            remplacements++;
            c = char2; // Mettre à jour le caractère pour le parcours
        }

        printf("Position (%d,%d) : %c\n", ligne, colonne, c);

        if (c == 'v') {
            ligne++;
            if (ligne >= longueurLigne) {
                printf("Sortie en bas\n");
                break;
            }

            lseek(fd, ligne * (longueurLigne + 1), SEEK_SET);
        } else if (c == '>') {
            colonne++;
            if (colonne >= longueurLigne) {
                printf("Sortie à droite\n");
                break;
            }

            lseek(fd, ligne * (longueurLigne + 1) + colonne, SEEK_SET);
        }
    }

    printf("%d remplacement(s) '%c' -> '%c'\n", remplacements, char1, char2);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage : %s <nom_fichier> <char1> <char2>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char char1 = argv[2][0];
    char char2 = argv[3][0];

    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    if (!estFichierValide(fd)) {
        fprintf(stderr, "Fichier invalide\n");
        close(fd);
        return 1;
    }

    remplacerEtSuivreFleches(fd, char1, char2);

    close(fd);
    return 0;
}

