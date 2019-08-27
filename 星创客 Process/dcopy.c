#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define err_log(errmsg) do{perror(errmsg); exit(1);}while(0)

int main(int argc, const char *argv[])
{
	char buf[32];
	long offset = 0;
	int fd_s, fd_t, count;

	
	if(argc != 3)
	{
		printf("cmd + srcfile + desfile\n");
		exit(1);
	}

	FILE *fpscr = fopen(argv[1],"r");
	if(NULL == fpscr)
		err_log("fail to fopen");
	
	FILE *fpdes = fopen(argv[2],"w");
	if(NULL == fpdes)
		err_log("fail to fopen");


	//1.打开源文件
	fd_s = open(argv[1], O_RDONLY);

	//2.打开目标文件
	fd_t = open(argv[2], O_RDWR|O_CREAT, 0666);

	//获取中间位置偏移量
	fseek(fpscr, 0, SEEK_END);
	offset = ftell(fpscr) / 2;
	printf("%ld\n", offset);
	
	pid_t pid;
	pid = fork();
	if(pid == -1)
	{
		perror("fail to fork");
		exit(1);
	}else if(pid)
	{
		//等待子进程结束
		int status;
		wait(&status);
		
		/*父进程*/
		printf("im parent:%d->%d\n",getpid(),getppid());
		
		fseek(fpscr, -offset, SEEK_END);
		fseek(fpdes, 0, SEEK_END);
		
		while(count = read(fd_s, buf, 32))
			write(fd_t, buf, count);
		
		
	}else
	{
		/*子进程*/
		printf("im child:%d->%d\n",getpid(),getppid());
		
		rewind(fpscr);
		rewind(fpdes);
		while(count = read(fd_s, buf, 32<offset?32:offset))
		{
			write(fd_t, buf, count);
			offset -= count;
		}
		
		exit(1);
	}
	printf("cccccc\n");
	return 0;
}
