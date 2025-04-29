#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("Type de fichier : Fichier regulier\n");
    } else if (S_ISDIR(mode)) {
        printf("Type de fichier : Repertoire\n");
    } else if (S_ISCHR(mode)) {
        printf("Type de fichier : Fichier special de caractere\n");
    } else if (S_ISBLK(mode)) {
        printf("Type de fichier : Fichier special de bloc\n");
    } else if (S_ISFIFO(mode)) {
        printf("Type de fichier : FIFO/Tube nommé\n");
    } else if (S_ISLNK(mode)) {
        printf("Type de fichier : Lien symbolique\n");
    } else if (S_ISSOCK(mode)) {
        printf("Type de fichier : Socket\n");
    } else {
        printf("Type de fichier : Inconnu\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nom_du_fichier>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat file_stat;

    if (stat(argv[1], &file_stat) == -1) {
        perror("Erreur lors de l'obtention des informations du fichier");
        return EXIT_FAILURE;
    }

    printf("Inode : %ld\n", (long)file_stat.st_ino);
    print_file_type(file_stat.st_mode);
    printf("Id proprietaire : %d\n", file_stat.st_uid);
    printf("Taille : %ld octets\n", (long)file_stat.st_size);
    printf("Derniere modification : %s", ctime(&file_stat.st_mtime));

    return EXIT_SUCCESS;
}

