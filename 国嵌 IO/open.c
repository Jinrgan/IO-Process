#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void main()
{
	int fd, fd1;
	char *buf = "987654321";
	char buf1[10];

	fd = open("/home/linux/文档/test.c", O_RDWR|O_CREAT, 0755);

	if(fd < 0)
		printf("open file fail!\n");

	fd1 = dup(fd);

	write(fd1, buf, 7);

	lseek(fd1, 0, SEEK_SET);

	read(fd1, buf1, 5);
//	buf1[5] = "\0";

	printf("buf1 is %s\n", buf1);

	close(fd);

}
