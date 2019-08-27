#include <time.h>
#include <stdio.h>

void main()
{
	time_t ctime;
	struct tm *tm;

	/* 获取日历时间 */
	ctime - time(NULL);

	/* 将日历时间转化为时间标准时间 */
	tm = gmtime(&ctime);

	printf("now is hour %d, min is %d\n", tm->tm_hour, tm->tm_min);
}
