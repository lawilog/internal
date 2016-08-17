#include <iostream>
#include <vector>
#include <array>
#include <forward_list>
#include "sum.hpp"
using namespace std;
using namespace LW;

int main()
{
	vector<int> v(111, 7);
	int s = sum(v.begin(), v.end());
	cout<< s <<endl;
	cout<< sum(v) <<endl;
	
	
	const unsigned N = 5;
	float a[N];
	for(unsigned i = 0; i < N; ++i)
		a[i] = 2*i+1;
	
	float x = sum(a, a+N);
	cout<< x <<endl;
	
	array<double,6> A;
	A.fill(7);
	cout<< sum(A.begin(), A.end()) <<endl;
	
	forward_list<int> L = {0, 1, 1, 1, 3, 3};
	L.unique();
	cout<< sum(L.begin(), L.end()) <<endl;
	
	return 0;
}
