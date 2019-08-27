#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void main()
{
	pid_t pid;

	pid = vfork();

	if(pid > 0)
	{
		//操作1
		wait(NULL);
		printf("this is father process\n");
		return ;
	}
	else
	{
		//操作2
		execl("/bin/ls", "ls", "/home/linux/", NULL);
		printf("this is child process\n");
		exit(0);
	}
}
