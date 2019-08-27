#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_func(void *arg)
{
	//printf("Im %d\n",pthread_self());
	char buf[9*1024*1024] = {};
	printf("i: %d\n", *(int *)arg);
	static int a = 200;
	pthread_exit(&a);
}

int main(int argc, const char *argv[])
{
	pthread_t tid;
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, 10*1024*1024);
	
	int i = 100;
	if(pthread_create(&tid, &attr, thread_func, &i) != 0)
	{
		perror("fail to pthread_create");
		exit(1);
	}
	int *p;
	pthread_join(tid, (void **)&p);
	printf("a: %d\n", *p);
	
	while(1);
	return 0;
}