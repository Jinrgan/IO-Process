#include<stdio.h>
#include<stdlib.h>

int main(int argc, const char *argv[])
{
	printf("aaaaa\n");
	freopen("test.txt","w+",stdout);
	printf("bbbbb\n");
	freopen("/dev/tty","r+",stdout);
	printf("ccccc\n");
	return 0;
}
