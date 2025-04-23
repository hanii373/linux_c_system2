#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Produit : 1\n");
        return EXIT_SUCCESS;
    }

    long product = 1;
    for (int i = 1; i < argc; i++) {
        char *endptr;
        errno = 0;
        long value = strtol(argv[i], &endptr, 10);
        if (errno != 0 || *endptr != '\0') {
            fprintf(stderr, "Erreur de conversion\n");
            return EXIT_FAILURE;
        }
        product *= value;
    }

    printf("Produit : %ld\n", product);
    return EXIT_SUCCESS;
}

