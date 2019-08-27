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
	
	//1.创建共享内存
	key_t key = ftok("/",'g');
	shmid = shmget(key, sizeof(struct shared_use_st), IPC_CREAT|0666);
	if(shmid == -1)
	{
		printf("creat share memory fail!\n");
		exit(EXIT_FAILURE);
	}
	printf("shmid : %d\n",shmid);
	
	//2.映射共享内存
	shared_stuff = (struct shared_use_st *)shmat(shmid, NULL, 0);
	
	//3.循环
	while(running)
	{
		while(shared_stuff->written_by_you == 1)
		{
			sleep(1);
			printf("wait read process!\n");
		}
		
		//3.1获取用户输入
		fgets(buffer, TEXT_SZ, stdin);
		
		//3.2将用户输入的字符串放入共享内存
		strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
		shared_stuff->written_by_you = 1;
		
		if(strncmp(buffer, "end", 3) == 0)
			running = 0;
	}
	
	//4.脱离共享内存
	shmdt((const void *)shared_stuff);
	
	return 1;
}