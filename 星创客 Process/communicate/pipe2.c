#include <stdio.h>
#include <unistd.h>

int main()
{
	int pfd[2];
	
	if(pipe(pfd) < 0) /*���������ܵ�*/
	{
		printf("pipe create error\n");
		return -1;
	}else{
		printf("pipe create success\n");
	}
	
	close(pfd[0]); //�رչܵ�������
	close(pfd[1]);
}