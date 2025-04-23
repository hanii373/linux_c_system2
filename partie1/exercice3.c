#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Verify the number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Convert the argument to an integer
    int n = atoi(argv[1]);

    // Count down from n to 0
    for (int i = n; i >= 0; i--) {
        printf("%d\n", i);
        sleep(1); // Pause for 1 second
    }

    return EXIT_SUCCESS;
}

