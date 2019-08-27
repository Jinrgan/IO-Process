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
	
	//������ֵ
	key = ftok("~/�ĵ�/��Ƕ/app/process", 1);
	
	//�������ź�������
	semid = semget(key, 1, IPC_CREAT);
	
//	ret = semctl(semid, 0, GETVAL);
//	printf("The value of sem is %d\n", ret);
	
	ret = semctl(semid, 0, SETVAL, 1);
	
	ret = semctl(semid, 0, GETVAL);
//	printf("The value of sem is %d\n", ret);
	
	//0.���ļ�
	fd = open("./board.txt", O_RDWR|O_APPEND);
		
	//1.1��ȡ�ź���
	sops.sem_num = 0;
	sops.sem_op = -1;
	semop(semid, &sops, 1);

	//1.�򹫸���ļ���д�롰��ѧ�Ρ�
	write(fd, "class math ", 11);
	
	//2.��ͣ��Ϣ
	sleep(10 );
	
	//3.�򹫸���ļ���д�롰ȡ����
	write(fd, "is cancel ", 11);
	
	//�ͷ��ź���
	sops.sem_num = 0;
	sops.sem_op = 1;
	semop(semid, &sops, 1);
	
	close(fd);
	
}