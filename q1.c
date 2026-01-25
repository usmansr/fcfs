#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int n = atoi(argv[1]); // N = number of children to create

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork error");
            break;
        } else if (pid == 0) {
            // Child's primary job
            printf("Process %d (PID: %ld) created by Parent (PPID: %ld)\n", 
                   i + 1, (long)getpid(), (long)getppid());

            // CRUCIAL LINE
            break; 
        }
        // Parent's primary job: nothing, just continue the loop
    }

    // Only the process that completed the loop runs this code
    if (getppid() == 1) {
        // Note: The original parent's PPID is NOT 1 initially, but
        // orphaned children's PPID becomes 1 (init/systemd) on some systems.
        // This check is a common way to identify non-original parents.
    } else {
        for (int i = 0; i < n; i++) {
            wait(NULL);
        }
        printf("Original Parent (PID: %ld) finished waiting for %d children.\n", 
               (long)getpid(), n);
    }

    return 0;
}

