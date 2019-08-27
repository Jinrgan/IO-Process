#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	DIR *dp;
	if(!(dp = opendir(argv[1])))
	{
		perror("fail to opendir");
		exit(1);
	}

	struct dirent *dir;
	while(dir = readdir(dp))
	{
		dir->d_type & DT_DIR ? putchar('d') : putchar('-');
		printf("name: %16s\tinode: %d\toffset:%d\n", dir->d_name, (int)dir->d_ino, (int)dir->d_off);
	}
	
	return 0;
}