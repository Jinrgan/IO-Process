#include "linkqueue.h"
/* 用链式队列实现如下功能：
 * 用户从键盘输入整数，程序将其入对;
 * 用户从键盘输入字母，程序将队头元素出队;
 * 并在每一次出队和入队之后打印队列元素。
 */
int main(int argc, const char *argv[])
{
	link_pqueue q;
	datatype data,t,ret;
	
	init_linkqueue(&q);

	while(1)
	{
		printf("请输入一个整数或字符:");
		ret=scanf("%d",&data);
		
		//输入整数时，入对
		if(ret == 1)
		{
			if(in_linkqueue(data,q))
				show_linkqueue(q);
		}
		else
		{
			//输入为字符时
			if(out_linkqueue(q,&t))
			{
				printf("out:%d\n",t);
				show_linkqueue(q);
			}
			//清空输入缓冲区
			while(getchar()!='\n');
		}
	}
	return 0;
}

