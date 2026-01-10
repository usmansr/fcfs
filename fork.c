#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main(void)
{
	printf("Hello, World\n");

	pid_t child_pid;
	child_pid = fork();

	if(child_pid == -1)
	{
		perror("Child process failed to be created");
	}

	if(child_pid == 0)
	{
		printf("I am child process: %ld \n", (long)getpid());
	} else	{
		printf("I am parent process: %ld \n", (long)getpid());
	}


	return 0;
}
