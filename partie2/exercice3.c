#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

	int success_count = 0;
    int failure_count = 0;

    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Erreur de fork");
            return 1;
        }
	if (pid == 0) {
            int num = atoi(argv[i]);
            if (num != 0) {
                printf("Enfant %d : 1/%d ~= %.4f\n", i, num, 1.0 / num);
                exit(EXIT_SUCCESS);
            } else {
                printf("Enfant %d : erreur pour \"%s\"\n", i, argv[i]);
                exit(EXIT_FAILURE);
            }
        }
    }
	for (int i = 1; i < argc; i++) {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == EXIT_SUCCESS) {
                success_count++;
            } else if (WEXITSTATUS(status) == EXIT_FAILURE) {
                failure_count++;
            }
        }
    }

    printf("Bilan : %d succès, %d échecs\n", success_count, failure_count);
    return 0;
}
