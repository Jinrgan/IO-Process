#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define TEXT_SZ 2048

struct shared_use_st
{
	int written_by_you;
	char some_text[TEXT_SZ];
};

int main()
{
	int running = 1;
	int shmid;
	struct shared_use_st *shared_stuff;
	char buffer[TEXT_SZ];
	
	//1.���������ڴ�
	key_t key = ftok("/",'g');
	shmid = shmget(key, sizeof(struct shared_use_st), IPC_CREAT|0666);
	if(shmid == -1)
	{
		printf("creat share memory fail!\n");
		exit(EXIT_FAILURE);
	}
	printf("shmid : %d\n",shmid);
	
	//2.ӳ�乲���ڴ�
	shared_stuff = (struct shared_use_st *)shmat(shmid, NULL, 0);
	
	//3.ѭ��
	while(running)
	{
		while(shared_stuff->written_by_you == 1)
		{
			sleep(1);
			printf("wait read process!\n");
		}
		
		//3.1��ȡ�û�����
		fgets(buffer, TEXT_SZ, stdin);
		
		//3.2���û�������ַ������빲���ڴ�
		strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
		shared_stuff->written_by_you = 1;
		
		if(strncmp(buffer, "end", 3) == 0)
			running = 0;
	}
	
	//4.���빲���ڴ�
	shmdt((const void *)shared_stuff);
	
	return 1;
}