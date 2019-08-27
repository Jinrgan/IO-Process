#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<errno.h>
#include<signal.h>
typedef struct msg{
	pid_t pid;
	char buf[124];
}msg_t;
void handler(int signo)
{
}

int main(int argc, const char *argv[])
{
	int shmid;
	key_t key = ftok("/",'g');
	shmid = shmget(key,128,IPC_CREAT|IPC_EXCL|0666);
	if(shmid == -1)
	{
		if(errno == EEXIST)
		{
			shmid = shmget(key,0,0);
		}else{
			perror("fail to shmget");
			exit(1);
		}
	}
	signal(SIGUSR1,handler);
	msg_t *p;
	if((p = shmat(shmid,NULL,0)) == (msg_t *)-1)
	{
		perror("fail to shmat");
		exit(1);
	}
	p->pid = getpid();
	pause();
	pid_t pid = p->pid;
	kill(pid,SIGUSR1);
	while(1)
	{
		pause();
		printf("recv:%s\n",p->buf);
		kill(pid,SIGUSR1);
	}




	return 0;
}
