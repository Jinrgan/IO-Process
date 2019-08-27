#include <unistd.h>
#include <stdio.h>

void main()
{
	pid_t pid = 0;
	int pipefd[2];
	char c_buf[10];
	
	/*2.�����ܵ�*/
	pipe(pipefd);
	
	/*1.�����ӽ���*/
	pid = fork();
	
	if(pid > 0)
	{
		/*������д������*/
		write(pipefd[1], "hello", 6);
		wait();
		close(pipefd[1]);
		exit(0);
	}
	
	if(pid == 0)
	{
		/*�ӽ��̶�����*/
		read(pipefd[0], c_buf, 6);
		printf("child read %s\n", c_buf);
		close(pipefd[0]);
		exit(0);
	}
}