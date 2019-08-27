#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	FILE *fp = fopen("test.txt","w+");
	if(NULL == fp)
	{
		perror("fail to fopen");
		exit(1);
	}

	fputc('a', fp);
	fflush(fp);
	fseek(fp, 0, SEEK_SET);
	printf("pos: %d\n", ftell(fp));
	char ch = fgetc(fp);
	printf("ch:%d\n", ch);
	printf("feof:%d\tferror:%d\n", feof(fp), ferror(fp));
	
	return 0;
}
