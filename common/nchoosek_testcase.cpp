#include <iostream>
#include <array>
#include "nchoosek.hpp"
using namespace std;
using namespace LW;

int main()
{
	const unsigned n = 4, k = 2;
	const unsigned P = choose(n, k);
	for(unsigned p = 1; p <= P; ++p)
	{
		array<int,k> c = combination<n,k>(p);
		cout<< c[0] <<" "<< c[1] <<endl;
	}
	return 0;
}
