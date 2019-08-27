#include <time.h>
#include <stdio.h>

void main()
{
	time_t ctime;
	struct tm *localtm;

	/* 获取日历时间 */
	ctime = time(NULL);

	/* 将日历时间转化为本地时间 */
	localtm = localtime(&ctime);

	printf("now local is hour %d, min %d\n", localtm->tm_hour, localtm->tm_min);
}
