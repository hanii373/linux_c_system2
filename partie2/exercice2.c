#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char *argv[]) {
		if (argc != 2){
			fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
		}
		int n = atoi(argv[1]);
		if (n < 0){
			fprintf(stderr, "Please provide a non-negative integer.\n");
        return 1;
   		}
		pid_t pid = getpid(); 
    		printf("Parent [PID=%d]\n", pid);

    	pid_t child_pid = fork();

    	if (child_pid < 0) {
        	perror("Fork failed");
        return 1;
    	}
		if (child_pid == 0) {
        pid_t ppid = getppid(); 
        for (int i = n; i >= 0; i--) {
            printf("Enfant [PPID=%d] : %d\n", ppid, i);
            sleep(1); 
        }
        return 0;
   		} 
		else {
        
        wait(NULL);
    	}

    return 0;
		
	}	
