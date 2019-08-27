#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int ret;
	if((pid = fork()) < 0)
	{
		perror("fork");
		exit(1);
	}
	
	if(pid == 0)
	{
		printf("child process exit...\n");
		exit(0);
	}else{
		printf("pid = %d\n", pid);
		raise(SIGSTOP);
		if((waitpid(pid, NULL, WNOHANG)) == 0)
		{
			kill(0, SIGKILL);
			printf("kill %d\n", pid);
		}
	}
}