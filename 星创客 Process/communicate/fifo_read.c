#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void main()
{
	if(mkfifo("./myfifo", 0666) != 0)
	{
		if(errno == EEXIST)
		{
			printf("the fifo is already exit\n");
		}else{
			perror("fail to mkfifo");
			exit(1);
		}
	}else{
		printf("success to mkfifo\n");
	}
	
	int fd = open("myfifo", O_RDONLY);
	if(fd < 0)
	{
		perror("fail to open");
		exit(1);
	}
	printf("open successfully\n");
	
	getchar();
	
	char buf[32] = {};
	read(fd, buf, 32);
	printf("buf: %s\n", buf);
	
	return;
}