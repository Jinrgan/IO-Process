#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int msqid = 0;

struct msgt
{
	long msgtype;
	char msgtext[1024];
};

void childprocess()
{
	struct msgt msgs;
	
//	while(1)
//	{
		//接受消息队列
		msgrcv(msqid, &msgs, sizeof(struct msgt), 0, 0);
		
		//打印消息队列中的数据
		printf("msg text: %s\n", msgs.msgtext);
//	}
	
	return;
}

void main()
{
	int i;
	int cpid;
	key_t key;
	key = ftok("/", 'e');
	
	//打开消息队列
	msqid =  msgget(1024, IPC_EXCL);
	
	//创建3个子进程
	for(i = 0; i < 3; i++)
	{
		cpid = fork();
		if(cpid < 0)
			printf("creat child process error!\n");
		else if(cpid == 0)
			childprocess();
	}
	
}