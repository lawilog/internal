#include <stdio.h>

int main()
{
	for(unsigned short x = 1; x < 16; ++x)
	{
		printf("%x |", x);
		for(unsigned short y = 1; y < 16; ++y)
		{
			if(x>y) printf("   ");
			else printf(" %2x", x*y);
		}
		printf("\n");
	}
	return 0;
}
