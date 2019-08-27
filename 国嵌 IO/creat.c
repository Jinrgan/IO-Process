#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void main()
{
	int fd;

	fd = creat("/home/linux/文档/test2.c", 0621);

	if(fd < 0)
		printf("creat file failed.");
}
