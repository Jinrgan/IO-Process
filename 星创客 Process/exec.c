#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, const int *argv[])
{
/*	if(execl("test","abc","def","xxx", NULL) == -1)
	{
		perror("fail to execl");
		exit(1);
	}
*/	
/*	char *buf[] = {"11","-l","-a", NULL};
	if(execvp("ls", buf) == -1)
	{
		perror("fail to execvp");
		exit(1);
	}
*/
	char *buf[] = {NULL};
	char *env[] = {"XXXX = HELLO", NULL};
	
	if(execvpe())
}