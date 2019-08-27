#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define err_log(errmsg) do{perror(errmsg); exit(1);}while(0)

int main(int argc, const char *argv[])
{
	FILE *fp = freopen("./test.txt","a+",stdout);
	if(NULL == fp)
		err_log("fail to fopen");

	time_t sec = 0;
	int line = 1;
	
	//重定向读取行数
/*	char linech[2] = {};
	fseek(fp, -22, SEEK_END);
	linech[0] = fgetc(fp);
	linech[1] = fgetc(fp);
	line = atoi(linech);
*/	
	//使用fgets计算行数
	char buf[8] = {};
	while(fgets(buf,8,fp) != NULL)
	{
		if(buf[strlen(buf) - 1] == '\n')
		{
			line++;
		}
	}
	
	//按字符计算行数
/*	rewind(fp);
	char ch;
	while(!feof(fp) && !ferror(fp))
	{
		ch = fgetc(fp);
		if('\n' == ch)
			line++;
	}
*/	
	while(1)
	{
		sec = time(NULL);
		struct tm *time = localtime(&sec);
		
		printf("%2d %d-%2d-%2d %2d:%2d:%2d\n", line++,\
		time->tm_year + 1900, time->tm_mon + 1, time->tm_mday,\
		time->tm_hour, time->tm_min, time->tm_sec);
		fflush(fp);
		
		sleep(1);

	}
	
	return 0;
}
