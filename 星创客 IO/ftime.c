#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define err_log(errmsg) do{perror(errmsg); exit(1);}while(0)

int main(int argc, const char *argv[])
{
	FILE *fp = freopen("./test.txt","w+",stdout);
	if(NULL == fp)
		err_log("fail to fopen");

	time_t sec = 0;
	int line = 1;

	while(1)
	{
		sec = time(NULL);
		struct tm *time = localtime(&sec);
		
		printf("%d %d-%d-%d %d: %d: %d\n", line,\
		time->tm_year + 1900, time->tm_mon + 1, time->tm_mday,\
		time->tm_hour, time->tm_min, time->tm_sec);
		fflush(fp);
		
		line++;
		sleep(1);

	}
	
	return 0;
}
