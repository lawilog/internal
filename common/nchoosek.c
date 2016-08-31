#include <stdio.h>

// calculate n choose k
unsigned choose(unsigned n, unsigned k)
{
	if(k == 0) return 1;
	return (n * choose(n - 1, k - 1)) / k;
}

// get the p'th choice of "n choose k", 1 <= p <= choose(n, k)
// output in c. must be int c[k];
void combination(int* c, const int n, const int k, const int p)
{
	int r, j = 0;
	for(int i = 0; i < k-1; ++i)
	{
		c[i] = (i == 0) ? 0 : c[i-1];
		do
		{
			++c[i];
			r = choose(n-c[i], k-i-1);
			j += r;
		} while(j < p);
		j -= r;
	}
	c[k-1] = (k>1 ? c[k-2] : 0) + p - j;
}

int main()
{
	const unsigned n = 4, k = 2;
	const unsigned P = choose(n, k);
	int c[k];
	for(unsigned p = 1; p <= P; ++p)
	{
		combination(c, n, k, p);
		printf("%i %i\n", c[0], c[1]);
	}
	return 0;
}
