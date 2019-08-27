#include <unistd.h>
#include <stdio.h>

void main()
{
	pid_t pid = 0;
	int pipefd[2];
	char c_buf[10];
	
	/*2.创建管道*/
	pipe(pipefd);
	
	/*1.创建子进程*/
	pid = fork();
	
	if(pid > 0)
	{
		/*父进程写入数据*/
		write(pipefd[1], "hello", 6);
		wait();
		close(pipefd[1]);
		exit(0);
	}
	
	if(pid == 0)
	{
		/*子进程读数据*/
		read(pipefd[0], c_buf, 6);
		printf("child read %s\n", c_buf);
		close(pipefd[0]);
		exit(0);
	}
}