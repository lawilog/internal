#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(0));
	int zufall = rand() % 100;
	int raten = 1;
	printf("Raten Sie eine Zahl zwischen 0 und 99\n");
	while(raten)
	{
		int R;
		scanf("%i", &R);
		if(R == zufall)
		{
			raten = 0;
			printf("Gefunden :-) \n");
		}
		else
		{
			if(R < zufall) printf("zu klein\n");
			else printf("zu gross\n");
		}
	}
	float kehrwert = 1.0 / zufall;
	printf("Der Kehrwert der Zahl ist %f\n", kehrwert);
	return 0;
}
