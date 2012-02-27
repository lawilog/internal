#include <stdio.h>

int main()
{
	int summe = 0;
	for(int k = 0; k < 10; k++)
	{
		int ungerade = 2*k + 1;
		summe = summe + ungerade;
		printf("%i \n", summe);
	}
	return 0;
}
