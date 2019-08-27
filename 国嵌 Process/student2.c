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

	//���ź�������
	semid = semget(key, 1, IPC_CREAT);
	
	//0.�򿪹����
	fd = open("./board.txt", O_RDWR|O_APPEND);
	
	ret = semctl(semid, 0, GETVAL);
	printf("The value of sem is %d\n", ret);
	
	//��ȡ�ź���
	sops.sem_num = 0;
	sops.sem_flg = -1;
	semop(semid, &sops, 1);
	
	//1.д�롰Ӣ��ο��ԡ�
	write(fd, "English exam ", 20);
	
	//�ͷ��ź���
	sops.sem_num = 0;
	sops.sem_flg = 1;
	semop(semid, &sops, 1);
	
	//2.�رչ����ļ�
	close(fd);
	
}