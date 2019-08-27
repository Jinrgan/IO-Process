#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd;
	fd = open("test.txt", O_RDWR|O_CREAT|O_TRUNC, 0666);
	if(-1 == fd)
	{
		perror("fail to open");
		exit(1);
	}
	
	int ret;
	ret = write(fd, "hello", 10);
	printf("ret: %d\n", ret);
	
	lseek(fd, 0, SEEK_SET);
	char buf[32] = {};
	ret = read(fd, buf, 32);
	printf("ret: %d\nbuf: %s\n", ret, buf);
	
	return 0;
}