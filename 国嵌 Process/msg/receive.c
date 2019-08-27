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
		//������Ϣ����
		msgrcv(msqid, &msgs, sizeof(struct msgt), 0, 0);
		
		//��ӡ��Ϣ�����е�����
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
	
	//����Ϣ����
	msqid =  msgget(1024, IPC_EXCL);
	
	//����3���ӽ���
	for(i = 0; i < 3; i++)
	{
		cpid = fork();
		if(cpid < 0)
			printf("creat child process error!\n");
		else if(cpid == 0)
			childprocess();
	}
	
}