#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    printf("Parent PID: %d, Parent PPID: %d\n", getpid(), getppid());

    pid = fork(); 

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { 
        printf("Child PID: %d, Child PPID: %d\n", getpid(), getppid());
        sleep(2); 
        printf("Child PID after sleep: %d, Child PPID after sleep: %d\n", getpid(), getppid());
    } else { 
        sleep(1); 
        printf("Parent waiting for child process...\n");
        wait(NULL); 
        printf("Parent process terminating after child...\n");
    }

    return EXIT_SUCCESS;
}

