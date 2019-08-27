#include <stdio.h>

int main()
{
	int ret;
	ret = alarm(4);
	printf("ret: %d\n", ret);
	sleep(2);
	
	ret = alarm(5);
	printf("ret: %d\n", ret);
	
	while(1)
	{
		printf("set over\n");
		sleep(1);
	}
	return 0;
}