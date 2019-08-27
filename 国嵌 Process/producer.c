#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void main()
{
	int fd;
	key_t key;
	int semid;
	struct sembuf sops;
	
	key = ftok("./", 2);
	
	//创建信号量
	semid = semget(key, 1, IPC_CREAT);
	semctl(semid, 0, SETVAL, 0);
	
	//创建产品-文件
	fd = open("./product.txt", O_RDWR|O_CREAT, 0775);
	
	//休息
	sleep(20);
	
	//向产品文件里面填充内容
	write(fd, "The product is finished!", 25);
	
	close(fd);
	
	//释放信号量
	sops.sem_num = 0;
	sops.sem_op = 1;
	sops.sem_flg = SEM_UNDO;
	semop(semid, &sops, 1);
}