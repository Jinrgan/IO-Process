#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<errno.h>

typedef union {
	int val;
}hello_t;

int main(int argc, const char *argv[])
{
	int semid;
	key_t key;
	key = ftok("/",'h');
	semid = semget(key, 2, IPC_CREAT|0666);
	if(semid == -1)
	{
		if(errno == EEXIST)
		{
			semid = semget(key, 0, 0);
		}else{
			perror("fail to semget");
			exit(1);
		}
	}else{
		hello_t hello;
		//信号量初始化
		hello.val = 0;
		semctl(semid,0,SETVAL,hello);
		hello.val = 1;
		semctl(semid,1,SETVAL,hello);
	}

	struct sembuf mysem[2];
	
	while(1)
	{
		//01
		mysem[0].sem_num = 0;
		mysem[0].sem_op = 1;
		mysem[0].sem_flg = 0;
		mysem[1].sem_num = 1;
		mysem[1].sem_op = -1;
		mysem[1].sem_flg = -1;
		semop(semid,mysem,2);
		//10
		
		printf("Hello\t");		
		sleep(1);
	}
	
	return 0;
}