#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BLOCK_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file_name> <character>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *file_name = argv[1];
    char target_char = argv[2][0];

    int fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char buffer[BLOCK_SIZE];
    ssize_t bytes_read;
    int count = 0;

    while ((bytes_read = read(fd, buffer, BLOCK_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == target_char) {
                count++;
            }
        }
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        return EXIT_FAILURE;
    }

    close(fd);

    printf("Caractère '%c' : %d occurrence(s)\n", target_char, count);
    return EXIT_SUCCESS;
}

