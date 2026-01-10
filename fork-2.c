#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error during fork");
    }

    if (child_pid == 0)
    {
        printf("I am Child: %ld \n", (long)getpid());
        execlp("/bin/a.out", "a.out", NULL);
        perror("execlp failed"); // Only runs if execlp fails
    }
    else
    {
        printf("I am Parent: %ld \n", (long)getpid());
        wait(NULL);
    }
        

    return 0;
}