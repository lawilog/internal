#include <stdio.h>

int foo()
{
	int a, b;
	do
	{
		scanf("%i", &a);
		if(a < 0) break;
		scanf("%i", &b);
		if(b < 0) break;
		printf("all good %i %i\n", a, b);
		return 0;
	} while(0);
	a = b = 0;
	printf("failed\n");
	return 1;
}

int main()
{
	return foo();
}
