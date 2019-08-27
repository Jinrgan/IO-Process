#include <stdio.h>

void main()
{
	FILE *fp;
	char *c_buf = "987654321";

	fp = fopen("/home/linux/文档/test.txt", "r+");

	fseek(fp, 8, SEEK_SET);

//	fread(c_buf, 1, 10, fp);

//	c_buf[10] = '\0';

//	printf("now we read %s\n", c_buf);

	fwrite(c_buf, 5, 1, fp);

	fclose(fp);
}
