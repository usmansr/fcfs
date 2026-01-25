#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#define LB_SIZE 1024
int main(int argc, char* argv[])
{
	printf("Hello, World\n");
	char* fullPathName = "/usr/bin/xeyes";
	char* myArgv[LB_SIZE];

	myArgv[0] = (char*) malloc(strlen(fullPathName) + 1);
	strcpy(myArgv[0], fullPathName);
	myArgv[1] = NULL;
	execvp(fullPathName, myArgv);

	perror("execvp failed"); // Only reached if execvp fails
	exit(0);
	return 0;
}
