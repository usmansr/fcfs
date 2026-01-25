#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid = fork();

	if(pid < 0)
	{
		perror("Fork Failed!");
	}

	if (pid == 0)
	{
		printf("Child PID: %ld\n", (long)getpid());
		execlp("/bin/ls", "ls", NULL);
	}
	else
	{
		printf("Parent PID: %ld\n", (long)getpid());
		printf("Parent waiting for child\n");

		// Sleep for 10 seconds.
                sleep(20);

		wait(NULL);
		printf("Parent's child done!\n");
	}

	return 0;
}
