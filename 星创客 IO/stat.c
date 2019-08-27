#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	struct stat st;
	
	if(stat(argv[1], &st))
	{
		perror("fail to stat");
		exit(1);
	}
	
	if(S_ISREG(st.st_mode))
		putchar('-');
	if(S_ISDIR(st.st_mode))
		putchar('d');
	if(st.st_mode & S_IRUSR)
		putchar('r');
	else
		putchar('-');
	if(st.st_mode & S_IWUSR)
		putchar('w');
	else
		putchar('-');
	if(st.st_mode & S_IXUSR)
		putchar('x');
	else
		putchar('-');

	printf("\n");		
	return 0;
}