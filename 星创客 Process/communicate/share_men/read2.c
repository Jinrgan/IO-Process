#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define TEXT_SZ 2048

int main()
{
	int shmid;
	char buf[128];
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	
	pthread_mutex_init(mutex,NULL);
	pthread_cond_init(cond,NULL);

	//1.创建、获取共享内存
	key_t key = ftok("/",'g');
	shmid = shmget(key, sizeof(buf), IPC_CREAT);

	//2.映射共享内存
	shared_stuff = (struct shared_use_st *)shmat(shmid, NULL, 0);
	
	//3.循环
	while(strncmp(shared_stuff->some_text, "end", 3))
	{
		//打印共享内存
		if(shared_stuff->written_by_you)
		{
			printf("write process writes %s\n", shared_stuff->some_text);
			shared_stuff->written_by_you = 0;
		}
	}
	
}