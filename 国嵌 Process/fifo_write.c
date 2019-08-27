#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void main()
{
	int fd;

	/*1.创建fifo文件*/
	mkfifo("/tmp/myfifo", 0666);

	/*2.打开fifo文件*/
	fd = open("/tmp/myfifo", O_WRONLY);

	/*3.写入数据到fifo文件*/
	write(fd, "hello fifo", 11);

	close(fd);
}
