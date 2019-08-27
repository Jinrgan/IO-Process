#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

void main()
{
	int fd = 0;
	key_t key;
	int semid;
	struct sembuf sops;
	int ret;
	
	//创建键值
	key = ftok("~/文档/国嵌/app/process", 1);

	//打开信号量集合
	semid = semget(key, 1, IPC_CREAT);
	
	//0.打开公告板
	fd = open("./board.txt", O_RDWR|O_APPEND);
	
	ret = semctl(semid, 0, GETVAL);
	printf("The value of sem is %d\n", ret);
	
	//获取信号量
	sops.sem_num = 0;
	sops.sem_flg = -1;
	semop(semid, &sops, 1);
	
	//1.写入“英语课考试”
	write(fd, "English exam ", 20);
	
	//释放信号量
	sops.sem_num = 0;
	sops.sem_flg = 1;
	semop(semid, &sops, 1);
	
	//2.关闭公告文件
	close(fd);
	
}