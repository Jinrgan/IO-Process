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

	char ch;
	int line = 0;

	while(!feof(fpscr) && !ferror(fpscr))
	{
		ch = fgetc(fpscr);
		if('\n' == ch)
			line++;
		fputc(ch, fpdes);
	}

	return 0;
}
