#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define NB_ARGUMENTS_MAX 10

int decouperCommande(char *commande, char *arguments[]) {
    int nbArguments = 0;
    int i = 0;
    while (commande[i] != '\0') {
        if (commande[i] == ' ') {
            commande[i] = '\0';
        } else if (
            (i == 0 || commande[i - 1] == '\0') &&
            commande[i] != '\0' &&
            nbArguments < NB_ARGUMENTS_MAX
        ) {
            arguments[nbArguments] = &commande[i];
            nbArguments++;
        }
        i++;
    }
    arguments[nbArguments] = NULL;
    return nbArguments;
}



int decouperCommande(char *commande, char *arguments[]);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command1> <command2> ...\n", argv[0]);
        return 1;
    }

    int success_count = 0, failure_count = 0;

    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Error during fork");
            return 1;
        }

        if (pid == 0) {
            // Child process
            char *arguments[NB_ARGUMENTS_MAX + 1];
            decouperCommande(argv[i], arguments);
            printf("Enfant %d [PID=%d] lance : %s\n", i, getpid(), arguments[0]);
            execvp(arguments[0], arguments); // Execute the command
            // If execvp fails
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            wait(&status); // Wait for the child process to finish
            if (WIFEXITED(status)) {
                int exit_code = WEXITSTATUS(status);
                printf("Parent : enfant PID=%d termine avec code %d\n", pid, exit_code);
                if (exit_code == 0) {
                    success_count++;
                } else {
                    failure_count++;
                }
            }
        }
    }

    printf("Bilan : %d succès, %d échecs\n", success_count, failure_count);
    return 0;
}

