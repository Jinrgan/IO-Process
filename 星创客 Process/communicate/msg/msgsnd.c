#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<errno.h>

typedef struct msg{
	long mtype;
	int a;
	char b;
}msg_t;

int main(int argc, const char *argv[])
{
	int msgid;
	key_t key;
	key = ftok("/", 'e');
	msgid = msgget(key, IPC_CREAT|IPC_EXCL|0666);
	if (msgid == -1)
	{
		if(errno == EEXIST)
			msgid = msgget(key, 0);
		else
		{
			perror("fail to msgget");
			exit(-1);
		}
	}
	printf("msgid: %d\n", msgid);
	
	msg_t mymsg, mymsg_r;
	mymsg.mtype = 1;
	mymsg.a = 100;
	mymsg.b = 'a';
	
	mymsg_r.mtype = 2;
	mymsg_r.a = 200;
	mymsg_r.b = 'b';
	
	msgsnd(msgid, &mymsg, sizeof(mymsg) - sizeof(long), 0);
	msgsnd(msgid, &mymsg_r, sizeof(mymsg_r) - sizeof(long), 0);
}