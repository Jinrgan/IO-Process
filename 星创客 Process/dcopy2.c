#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

	//1.��Դ�ļ�
	fd_s = open(argv[1], O_RDONLY);

	//2.��Ŀ���ļ�
	fd_t = open(argv[2], O_RDWR|O_CREAT, 0666);

	//��ȡ�м�λ��ƫ����
	offset = lseek(fd_s, 0, SEEK_END) / 2;
	printf("%ld\n", offset);
	
	pid_t pid;
	pid = fork();
	if(pid == -1)
	{
		perror("fail to fork");
		exit(1);
	}else if(pid)
	{
		/*������*/
		printf("im parent:%d->%d\n",getpid(),getppid());
		
		lseek(fd_s, offset, SEEK_SET);
		lseek(fd_t, offset, SEEK_SET);
		
		while(count = read(fd_s, buf, 32))
			write(fd_t, buf, count);
		
		
	}else
	{
		/*�ӽ���*/
		printf("im child:%d->%d\n",getpid(),getppid());
		
		//�����ļ�ָ�룬�������
		close(fd_s);
		close(fd_t);
		fd_s = open(argv[1],O_RDONLY);
		fd_t = open(argv[2],O_WRONLY);

		lseek(fd_s, 0, SEEK_SET);
		lseek(fd_t, 0, SEEK_SET);
		while(count = read(fd_s, buf, 32<offset?32:offset))
		{
			write(fd_t, buf, count);
			offset -= count;
		}
	}
	return 0;
}
