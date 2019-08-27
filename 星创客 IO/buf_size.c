#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
	FILE *fp = fopen("test.txt","w");
	if(NULL == fp)
	{
		perror("fail to fopen");
		exit(1);
	}

	printf("stdout:%ld\n", stdout->_IO_buf_end - stdout->_IO_buf_base);
	printf("stdout:%ld\n", stdout->_IO_buf_end - stdout->_IO_buf_base);
	printf("fp:%ld\n", fp->_IO_buf_end - fp->_IO_buf_base);
	fputc('c', fp);
	printf("fp:%ld\n", fp->_IO_buf_end - fp->_IO_buf_base);
	printf("stdin:%ld\n", stdin->_IO_buf_end - stdin->_IO_buf_base);
	fgetc(stdin);
	printf("stdin:%ld\n", stdin->_IO_buf_end - stdin->_IO_buf_base);


	return 0;
}
