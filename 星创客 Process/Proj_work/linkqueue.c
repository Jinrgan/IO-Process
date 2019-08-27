#include "linkqueue.h"

void init_linkqueue(link_pqueue *Q)
{
	//申请front和rear的空间
	*Q=(link_pqueue)malloc(sizeof(link_queue));
	if((*Q)==NULL)
	{
		perror("malloc");
		exit(-1);
	}
	//申请头结点空间
	(*Q)->front=(linkqueue_pnode)malloc(sizeof(linkqueue_node));
	if((*Q)->front==NULL)
	{
		perror("malloc");
		exit(-1) ;
	}

	(*Q)->front->next=NULL;
	(*Q)->rear=(*Q)->front;

	return;
}
//入

bool in_linkqueue(datatype data, link_pqueue q)
{
	linkqueue_pnode  new;

	//申请数据结点空间
	new = (linkqueue_pnode)malloc(sizeof(linkqueue_node));
	if(new == NULL)
	{
		puts("入队失败！");
		return false;
	}
	//将数据存储在申请的空间
	new->data = data;
	
	//将new指向的结点插入到链式队列中
	new->next = q->rear->next;
	q->rear->next = new;
	
	//让rear指针指向新的队尾结点
	q->rear = q->rear->next;

	return true;
}

bool is_empty_linkqueue(link_pqueue q)
{
	if(q->rear == q->front)
		return true;
	else
		return false;
}

//出队
bool out_linkqueue(link_pqueue q,datatype *D)
{
	linkqueue_pnode t;
	//判断队列是否空
	if(is_empty_linkqueue(q)){
		printf("队列已空!\n");
		return false;
	}

	//出队
	t = q->front;
	q->front = q->front->next;
	*D = q->front->data;
	free(t);
	t = NULL;

	return true;
}

void show_linkqueue(link_pqueue q)
{
	linkqueue_pnode p;
	if(is_empty_linkqueue(q))
		return;
	//非空时，从对头打印到队尾
	for(p = q->front->next; p != NULL; p = p->next)
	{
		printf("%d\t",p->data);
	}
	printf("\n");
}
