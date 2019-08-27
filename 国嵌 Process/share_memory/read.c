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
	int running = 1;
	struct shared_use_st *shared_stuff;

	//1.´´½¨¡¢»ñÈ¡¹²ÏíÄÚ´æ
	key_t key = ftok("/",'g');
	shmid = shmget(key, sizeof(struct shared_use_st), IPC_CREAT);
	
	//2.Ó³Éä¹²ÏíÄÚ´æ
	shared_stuff = (struct shared_use_st *)shmat(shmid, NULL, 0);
	
	shared_stuff->written_by_you = 0;
	
	//3.Ñ­»·
	while(running)
	{
		//´òÓ¡¹²ÏíÄÚ´æ
		if(shared_stuff->written_by_you);
		{
			printf("write process writes %s\n", shared_stuff->some_text);
			shared_stuff->written_by_you = 0;
			
			if(strncmp(shared_stuff->some_text, "end", 3) == 0)
				running = 0;
		}
	}
	
	//4.ÍÑÀë¹²ÏíÄÚ´æ
	shmdt((const void *)shared_stuff);
	
	//5.É¾³ý¹²ÏíÄÚ´æ
	shmctl(shmid, IPC_RMID, 0);

	return 1;
}