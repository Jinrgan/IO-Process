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
	
	//创建打开信号量集合
	semid = semget(key, 1, IPC_CREAT);
	
//	ret = semctl(semid, 0, GETVAL);
//	printf("The value of sem is %d\n", ret);
	
	ret = semctl(semid, 0, SETVAL, 1);
	
	ret = semctl(semid, 0, GETVAL);
//	printf("The value of sem is %d\n", ret);
	
	//0.打开文件
	fd = open("./board.txt", O_RDWR|O_APPEND);
		
	//1.1获取信号量
	sops.sem_num = 0;
	sops.sem_op = -1;
	semop(semid, &sops, 1);

	//1.向公告板文件里写入“数学课”
	write(fd, "class math ", 11);
	
	//2.暂停休息
	sleep(10 );
	
	//3.向公告板文件里写入“取消”
	write(fd, "is cancel ", 11);
	
	//释放信号量
	sops.sem_num = 0;
	sops.sem_op = 1;
	semop(semid, &sops, 1);
	
	close(fd);
	
}