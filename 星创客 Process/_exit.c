#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Using exit...\n");
	printf("This is the end");
	_exit(0);
}