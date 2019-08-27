#include <sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid == -1)
	{
		perror("fail to fork");
		exit(1);
	}else if(pid == 0)
		exit(3);
	else{
		int status;
		wait(&status);
		printf("status: %d\n", WEXITSTATUS(status));
	}
	
	return 0;
}