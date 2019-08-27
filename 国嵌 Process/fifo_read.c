#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void main()
{
	char c_buf[15];
	int fd;
	
	fd = open("/tmp/myfifo", O_RDONLY);
	
	read(fd, c_buf, 11);
	
	printf("read %s\n", c_buf);
	
	close(fd);
	
	unlink("/tmp/myfifo");
}