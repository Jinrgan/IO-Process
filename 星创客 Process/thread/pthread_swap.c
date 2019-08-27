#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define N 100
typedef struct msg{
	char buf[N];
	int len;
}msg_t;

pthread_mutex_t mutex;

void *swap(void *arg)
{
	msg_t *p = (msg_t *)arg;
	int i;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		for(i = 0; i < p->len / 2; i ++)
		{
			p->buf[i] = p->buf[i] ^ p->buf[p->len - i - 1];
			p->buf[p->len - i - 1] = p->buf[i] ^ p->buf[p->len - i - 1];
			p->buf[i] = p->buf[i] ^ p->buf[p->len - i - 1];
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void *show(void *arg)
{
	msg_t *p = (msg_t *)arg;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("%s\n", p->buf);
		pthread_mutex_unlock(&mutex);
		
		sleep(1);
	}
}

int main()
{
	msg_t mymsg = {"123456789", 9};
	pthread_t tid[2];
	if(pthread_create(&tid[0], NULL, swap, &mymsg) == -1)
	{
		perror("fail to pthread_create");
		exit(1);
	}
	if(pthread_create(&tid[1], NULL, show, &mymsg) == -1)
	{
		perror("fail to pthread_create");
		exit(1);
	}
	
	pause();
	return 0;
}