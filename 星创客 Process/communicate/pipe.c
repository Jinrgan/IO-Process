#include <stdio.h>
#include <stdlib.h>

void main()
{
	int fd[2], i=0;
	char buf[65538] = {};

	if(pipe(fd) != 0)
	{
		perror("fail to pipe");
		exit(1);
	}

	while(i < 32768)
	{
		write(fd[1], "aa", 2);
		printf("%d\t", i++);	
	}
	read(fd[0], buf, 65538);
	printf("%s\n", buf);

	close(fd);
}
