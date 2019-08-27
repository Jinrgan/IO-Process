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
	
	//创建消息队列
	key_t key;
	key = ftok("/", 'e');
	msqid =  msgget(1024, IPC_CREAT);
	
	//
	while(1)
	{
		printf("please input message type, 0 for quit!\n");
		//获取消息队列
		scanf("%d", &msg_type);
		
		//如果用户输入的消息类型为0，退出该循环
		if(msg_type == 0)
			break;
		
		//获取消息数据
		printf("please input message content!\n");
		scanf("%s", str);
		
		msgs.msgtype = msg_type;
		strcpy(msgs.msgtext, str);
		
		//发送消息
		msgsnd(msqid, &msgs, sizeof(struct msgt), 0);

	}
	
	//删除消息队列
	msgctl(msqid, IPC_RMID, NULL);
}