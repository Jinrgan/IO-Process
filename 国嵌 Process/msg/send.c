#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgt
{
	long msgtype;
	char msgtext[1024];
};

void main()
{
	int msqid;
	int msg_type;
	char str[256];
	struct msgt msgs;
	
	//������Ϣ����
	key_t key;
	key = ftok("/", 'e');
	msqid =  msgget(1024, IPC_CREAT);
	
	//
	while(1)
	{
		printf("please input message type, 0 for quit!\n");
		//��ȡ��Ϣ����
		scanf("%d", &msg_type);
		
		//����û��������Ϣ����Ϊ0���˳���ѭ��
		if(msg_type == 0)
			break;
		
		//��ȡ��Ϣ����
		printf("please input message content!\n");
		scanf("%s", str);
		
		msgs.msgtype = msg_type;
		strcpy(msgs.msgtext, str);
		
		//������Ϣ
		msgsnd(msqid, &msgs, sizeof(struct msgt), 0);

	}
	
	//ɾ����Ϣ����
	msgctl(msqid, IPC_RMID, NULL);
}