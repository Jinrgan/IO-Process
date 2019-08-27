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
	int shmid;
	struct shared_use_st *shared_stuff;

	//1.��������ȡ�����ڴ�
	key_t key = ftok("/",'g');
	shmid = shmget(key, sizeof(struct shared_use_st), IPC_CREAT);
	
	//2.ӳ�乲���ڴ�
	shared_stuff = (struct shared_use_st *)shmat(shmid, NULL, 0);
	
	shared_stuff->written_by_you = 0;
	
	//3.ѭ��
	while(strncmp(shared_stuff->some_text, "end", 3))
	{
		//��ӡ�����ڴ�
		if(shared_stuff->written_by_you)
		{
			printf("write process writes %s\n", shared_stuff->some_text);
			shared_stuff->written_by_you = 0;
		}
	}
	
	//4.���빲���ڴ�
	shmdt((const void *)shared_stuff);
	
	//5.ɾ�������ڴ�
	shmctl(shmid, IPC_RMID, 0);

	return 1;
}