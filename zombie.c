#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
    printf("Hello, World\n");

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        printf("Child process: %ld exiting...\n", (long)getpid());
        exit(0);   // Child exits immediately
    } 
    else {
        // Parent process
        printf("Parent process: %ld sleeping...\n", (long)getpid());
        
        sleep(60);
        
        printf("Parent woke up.\n");
    }

    return 0;
}
