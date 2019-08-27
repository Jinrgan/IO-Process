#include <stdio.h>
#include <unistd.h>

int main()
{
	int pfd[2];
	
	if(pipe(pfd) < 0) /*创建无名管道*/
	{
		printf("pipe create error\n");
		return -1;
	}else{
		printf("pipe create success\n");
	}
	
	close(pfd[0]); //关闭管道描述符
	close(pfd[1]);
}