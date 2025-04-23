#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    printf("Parent PID: %d, Parent PPID: %d\n", getpid(), getppid());

    pid = fork(); // Create child process

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        printf("Child PID: %d, Child PPID: %d\n", getpid(), getppid());
        sleep(2); // Child waits for 2 seconds
        printf("Child PID after sleep: %d, Child PPID after sleep: %d\n", getpid(), getppid());
    } else { // Parent process
        sleep(1); // Parent waits for 1 second
        printf("Parent process terminating...\n");
    }

    return EXIT_SUCCESS;
}

