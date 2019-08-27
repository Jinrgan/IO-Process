#include <pthread.h>
#include <stdio.h>

int number = 0;
pthread_t thread[3];
pthread_mutex_t mut;

pthread_cond_t cond_ready=PTHREAD_COND_INITIALIZER;

void *pthread_func1()
{
	while(1)
	{
		pthread_mutex_lock(&mut);
		
		while(number != 0)
		{
			pthread_cond_wait(&cond_ready, &mut);
		}
		
		printf("Hello ");
		number++;
		pthread_cond_broadcast(&cond_ready);
		
		pthread_mutex_unlock(&mut);		
	}
}

void *pthread_func2()
{
	while(1)
	{
		pthread_mutex_lock(&mut);

		while(number != 1)
		{
			pthread_cond_wait(&cond_ready, &mut);
		}
		
		printf("the ");
		number++;
		pthread_cond_broadcast(&cond_ready);
		
		pthread_mutex_unlock(&mut);		
	}
}

void *pthread_func3()
{
	while(1)
	{
		pthread_mutex_lock(&mut);

		while(number != 2)
		{
			pthread_cond_wait(&cond_ready, &mut);
		}
		
		printf("world!\n");
		number = 0;
		pthread_cond_broadcast(&cond_ready);
		
		pthread_mutex_unlock(&mut);		
	}
}

int main()
{
	pthread_mutex_init(&mut, NULL);


	pthread_create(&thread[0], NULL, pthread_func1, NULL);
	pthread_create(&thread[1], NULL, pthread_func2, NULL);
	pthread_create(&thread[2], NULL, pthread_func3, NULL);
	
	pause();
}