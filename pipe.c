#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char msg1[] = "message 1";
	char msg2[] = "message 2";
	char buffer[50];
	int fd[2];

	if(pipe(fd) >= 0)
	{
		write(fd[1], msg1, sizeof(msg1));
		write(fd[1], msg2, sizeof(msg2));
		write(fd[1], "message", 8);

		for(int i = 0; i < 3; i++)
		{
			read(fd[0], buffer, 10);
			printf("%s \n",buffer);
		}
	}
	return 0;
}
