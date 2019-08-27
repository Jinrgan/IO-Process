#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(int argc, char **argv)
{
	int fd_s, fd_t;
	int count;
	char buf[512];

//1.打开源文件
	fd_s = open(argv[1], O_RDONLY);

//2.打开目标文件
	fd_t = open(argv[2], O_RDWR|O_CREAT, 0666);

//3.4.读取源文件数据, 将读取出的源文件数据写入目标文件
	while(count = read(fd_s, buf, 512))
		write(fd_t, buf, count);

//5.关闭文件
	close(fd_s);
	close(fd_t);
}
