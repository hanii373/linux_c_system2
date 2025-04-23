#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to check if a number is prime
int estPremier(long n) {
    if (n <= 1) return 0;
    for (long d = 2; d * d <= n; d++) {
        if (n % d == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    
    int nb_premiers = 0;      // Count of prime numbers
    int nb_non_premiers = 0;  // Count of non-prime numbers
    int nb_erreurs = 0;       // Count of conversion errors

    for (int i = 1; i < argc; i++) {
        pid_t pid = fork(); // Create a child process
        if (pid < 0) {
            perror("Erreur de fork");
            return 1;
        }

        if (pid == 0) {
            // Child process
            char *endptr;
            long num = strtol(argv[i], &endptr, 10); // Convert argument to a long integer

            if (*endptr != '\0') {
                // Conversion error
                printf("Enfant %d : erreur pour \"%s\".\n", i, argv[i]);
                exit(2); // Exit with code 2 for conversion error
            }

            if (estPremier(num)) {
                // Number is prime
                printf("Enfant %d : %ld est premier.\n", i, num);
                exit(0); // Exit with code 0 for prime
            } else {
                // Number is not prime
                printf("Enfant %d : %ld n'est pas premier.\n", i, num);
                exit(1); // Exit with code 1 for non-prime
            }
        }
    }

    // Parent process
    for (int i = 1; i < argc; i++) {
        int status;
        wait(&status); // Wait for child process to finish
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            if (exit_code == 0) {
                nb_premiers++; // Child exited with code 0: prime number
            } else if (exit_code == 1) {
                nb_non_premiers++; // Child exited with code 1: non-prime number
            } else if (exit_code == 2) {
                nb_erreurs++; // Child exited with code 2: conversion error
            }
        }
    }

    // Final summary
    printf("Bilan : %d nombres premiers, %d nombres non premiers, %d erreurs de conversion\n",
           nb_premiers, nb_non_premiers, nb_erreurs);

    return 0;
}

