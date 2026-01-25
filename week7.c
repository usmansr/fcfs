#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int n, fd;
    char* buffer;
    printf("Enter Text: \n");
    n = read(0, buffer, 50);
    write(1, buffer, n);

    return 0;
}
