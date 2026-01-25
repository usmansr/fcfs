#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
	int n = atoi(argv[1]);
	for (int i = 0; i < n; i++) 
	{
		pid_t child_pid = fork();
		if (child_pid < 0)
		{
			perror("fork failed");
		}
		else if (child_pid == 0)
		{
			// Child Space
			printf("Child %d → PID: %ld (Parent PID: %ld)\n", i + 1,(long)getpid(), (long)getppid());
			exit(0); // Child must exit so it does NOT create more children
		}
	}
	// Parent waits for all children
	for (int i = 0; i < n; i++)
	{
		wait(NULL);
	}
	printf("Parent PID: %ld — All children finished.\n", (long)getpid());
	return 0;
}
