#include <stdio.h>
#include <unistd.h>
int main() {
    // Get and print the process ID (PID)
    printf("PID = %d\n", getpid());
    
    // Get and print the parent process ID (PPID)
    printf("PPID = %d\n", getppid());
    
    return 0;
}

