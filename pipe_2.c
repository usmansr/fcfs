#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int fd1[2], fd2[2];
	char msg1[20] = "Hello-1";
	char msg2[20] = "Hello-2";
	char buffer[20];

	if(pipe(fd1) < 0 && pipe(fd2) < 0)
	{
		perror("pipe not created!");
	}

	int pid = fork();
	if(pid > 0)
	{
		close(fd1[0]);
		close(fd2[1]);

		printf("In Parent, writing pipe-1's message: %s \n", msg1);
		write(fd1[1], msg1, sizeof(msg1));
		read(fd2[0], buffer, sizeof(buffer));
		printf("In Parent, reading pipe-2's message: %s \n", buffer);

	}
	else if(pid == 0)
	{
		close(fd2[0]);
		close(fd1[1]);
		read(fd1[0], buffer, sizeof(buffer));
		printf("In Child, reading pipe-1's message: %s \n", buffer);
		printf("In Child, writing pipe-2's message: %s \n", msg2);
		write(fd2[1], msg1, sizeof(msg1));
	}
	return 0;
}
