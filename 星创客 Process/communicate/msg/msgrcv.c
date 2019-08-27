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

	msg_t mymsg;
	
	msgrcv(msgid, &mymsg, sizeof(mymsg) - sizeof(long), 0, 0);
	printf("a: %d\tb: %c\n", mymsg.a, mymsg.b);
	msgctl(msgid, IPC_RMID, NULL);
	
	return 0;
}