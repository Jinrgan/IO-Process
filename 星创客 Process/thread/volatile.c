#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread_func(void *arg)
{
	sleep(2);
	*(int *)arg = 0;
}

int main()
{
	int a = 1;
	pthread_t tid;
	pthread_create(&tid, NULL, thread_func, (int *)&a);
	
	while(a);
	printf("aaaaaaaaaaaaaa\n");
	
	return 0;
}