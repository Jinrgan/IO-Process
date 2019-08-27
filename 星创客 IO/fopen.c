#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE * fp = fopen("test.txt", "a");
	if(NULL == fp)
	{
		perror("fail to fopen");
		exit(1);
	}
	printf("success to fopen\n");

	return 0;
}
