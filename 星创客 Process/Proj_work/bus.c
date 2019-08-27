#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t pid;

void handler_ch(int sign_no)
{
	switch (sign_no)
	{
		case SIGINT: 
			kill(getppid(), SIGUSR1);
			break;
		case SIGQUIT: 
			kill(getppid(), SIGUSR2);
			break;
		case SIGUSR1: 
			puts("please get off the bus\n");
			exit(0);
	}
}

void handler_fa(int sign_no)
{
	switch (sign_no)
	{
		case SIGUSR1: 
			printf("let's gogogo\n");
			break;
		case SIGUSR2: 
			printf("stop the bus\n");
			break;
		case SIGTSTP: 
			kill(pid, SIGUSR1);
			break;
	}
}

int main()
{
	int ret;

	if((pid = fork()) < 0)
	{
		perror("fork");
		exit(1);
	}
	
	if(pid == 0)
	{
		/*子进程*/
		signal(SIGINT, handler_ch);
		signal(SIGQUIT, handler_ch);
		signal(SIGUSR1, handler_ch);
		signal(SIGUSR2, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		while(1)
			pause();

		printf("child process exit...\n");
		exit(0);
	}else{
		/*父进程*/
		signal(SIGUSR1, handler_fa);
		signal(SIGUSR2, handler_fa);
		signal(SIGTSTP, handler_fa);
		signal(SIGCHLD, handler_fa);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wait(NULL);
	}
	return 0;
}