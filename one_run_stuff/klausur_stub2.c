#include <stdio.h>

int main()
{
	int U = 230;
	printf("Die Standard-Spannung beträgt %i Volt.\n", U);
	printf("Geben Sie eine neue Spannung ein: ");
	scanf("%i", &U);
	if(180 <= U && U <= 250)
	{
		printf("Die eingegebene Spannung ist OK.\n");
	}
	else
	{
		printf("Die eingegebene Spannung liegt ausserhalb des erlaubten Bereichs.\n");
	}
	return 0;
}
