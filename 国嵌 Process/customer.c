#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

void main()
{
	key_t key;
	int semid;
	struct sembuf sops;
	int ret;

	key = ftok("./", 2);
	semid = semget(key, 1, IPC_CREAT);

	//获取信号量
	sops.sem_num = 0;
	sops.sem_op = -1;
	sops.sem_flg = SEM_UNDO;
	ret = semop(semid, &sops, 1);
	printf("ret is %d\n", ret);
	
	//取走产品文件
	system("cp ./product.txt ./ship/");
}