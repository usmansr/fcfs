#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int main(void)
{
	pid_t n, fd;
	char buffer[50];

	fd = open("Abc.txt", O_CREAT | O_RDWR, 0777);

	n = read(fd, buffer, 50);
	write(1, buffer, n);

	n = read(0, buffer, 50);
	write(fd, buffer, n);

	close(fd);

	return 0;
}
