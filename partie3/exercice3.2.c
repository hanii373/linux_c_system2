#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BLOCK_SIZE 1024

void count_occurrences(char character, const char *file_name, int child_num) {
    char buffer[BLOCK_SIZE];
    ssize_t bytes_read;
    int count = 0;

    int fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = read(fd, buffer, BLOCK_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == character) {
                count++;
            }
        }
    }

    printf("Enfant %d (caractère '%c') : %d occurrence(s)\n", child_num, character, count);
    close(fd);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file_name> <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *file_name = argv[1];
    char *search_string = argv[2];
    int length = strlen(search_string);

    for (int i = 0; i < length; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            count_occurrences(search_string[i], file_name, i + 1);
        } else if (pid < 0) {
            perror("Error creating child process");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < length; i++) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}

