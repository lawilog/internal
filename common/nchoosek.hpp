#ifndef _LW_NCHOOSE_K
#define _LW_NCHOOSE_K

#include <array>

namespace LW {

// calculate n choose k
unsigned choose(unsigned n, unsigned k)
{
	if(k == 0) return 1;
	return (n * choose(n - 1, k - 1)) / k;
}

// return the p'th choice of "n choose k", 1 <= p <= choose(n, k)
// entries of return value will be in [1, n]
template <int n, int k>
std::array<int,k> combination(const int p)
{
	std::array<int,k> c;
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
	return c;
}

}

#endif // _LW_NCHOOSE_K
