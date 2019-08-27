#include <stdio.h>
#include <signal.h>

void handler()
{
	sleep(2);
	printf("I'm ctrl+c\n");
}

int main()
{
	signal(SIGINT, handler);
	pause();
	printf("after pause\n");
	
	return 0;
}