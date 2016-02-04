#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	const unsigned long N = argc>1 ? 1000000 * atoi(argv[1]) : 2;
	unsigned long n;
	float x, xx, err = 0.0;
	for(n = 1; n < N; ++n)
	{
		x = n;
		while(x > 1.0)
		{
			xx = x / 2.0;
			if(xx - (unsigned long)(xx) > 0.25 ) x = 3.0*x + 1.0;
			else x = xx;
		}
		err += x>1.0 ? 1.0-x : x-1.0;
	}
	printf("err = %e\n", err);
	return 0;
}

