#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
	int id = 0;
	id = getpid();
	printf("process id is %d\n", id);
}
