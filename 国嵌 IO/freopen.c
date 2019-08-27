#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
	FILE * fp;
	fp = fopen("test.c", "r+");
	if(NULL == fp)
	{
		perror("fopen");
		exit(1);
	}

	printf("%d\n", fp->_IO_buf_end - fp->_IO_buf_base);
	freopen("test.c", "w", stdout);
	printf("before freopen\n");

	return 0;
}
