#include <stdio.h>
#include <unistd.h>

int main ()
{
    int n,fd;
    char* buff[50];  // declaring buffer
    printf("Enter the text.\n");
    // read from the keyboard, Specify 0 as fd for std input Device
    n = read(0,buff,50);
    //n is the number of character stored
    // Write message on the screen, Specify 1 as fd for output devices
    write(1,buff,n);

    return 0;
}
