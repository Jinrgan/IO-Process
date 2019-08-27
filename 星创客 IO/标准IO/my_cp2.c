#include <stdio.h>
#include <stdlib.h>

#define err_log(errmsg) do{perror(errmsg); exit(1);}while(0)

int main(int argc, const char *argv[])
{
	if(argc != 3)
	{
		printf("cmd + srcfile + desfile\n");
		exit(1);
	}

	FILE *fpscr = fopen(argv[1],"r");
	if(NULL == fpscr)
		err_log("fail to fopen");

	FILE *fpdes = fopen(argv[2],"w");
	if(NULL == fpdes)
		err_log("fail to fopen");

	char ch, buf[32] = {};
	int line = 0;
	
	while(1)
	{
		if(NULL == fgets(buf, 32, fpscr))
			break;
		if(buf[strlen(buf) - 1] == '\n')
		{
			line++;
		}
		fputs(buf, fpdes);
		line++;
	}
	printf("line: %d\n", line);

	return 0;
}
