#include <unistd.h>
#include <stdio.h>

void main()
{
	pid_t pid;

	pid = fork();

	if(pid > 0)
	{
		//操作1
		printf("this is father process\n");
		exit(0);
	}
	else
	{
		//操作2
		printf("this is child process\n");
		exit(0);
	}

	printf("pid is %d\n", pid);

//	exit(0);
}
