#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
            printf("Enfant %d [PID=%d] lance : %s\n", i, getpid(), argv[i]);
            execlp(argv[i], argv[i], NULL); // Execute the command
            // If execlp fails
            perror("execlp failed");
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


