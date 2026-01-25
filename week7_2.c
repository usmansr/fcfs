#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    int n, fd;
    char buffer[50];

    fd = open("usman.txt", O_CREAT | O_RDWR,0777);

    n = read(fd, buffer, 50);

    write(1, buffer, n);

    printf("Enter Text: \n");

    n = read(0, buffer, 50);
    write(fd, buffer, 50);

    return 0;
}


