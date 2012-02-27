#include <stdio.h>

int main()
{
	FILE* fp;
	if((fp = fopen("/etc/shadow", "r")) == NULL)
	{
		printf("Konnte Datei nicht oeffnen.\n");
		return;
	}
	char c;
	while(!feof(fp))
	{
		c=fgetc(fp);
		printf("%c",c);
	}
	fclose(fp);
	return 0;
}
