#include <iostream>
#include "vector2d.hpp"
using namespace std;
using namespace LW;

int main()
{
	vector2d<int> a(3,4);
	for(unsigned i = 0; i < 3; ++i)
		for(unsigned j = 0; j < 4; ++j)
			a(i,j) = 10*i + j;
	
	vector2d<int> b = a;
	
	a.resize(1, 15);
	for(unsigned k = 0; k < 15; ++k)
		cout<< a.at(0, k) <<endl;
	
	vector2d<bool> B(32, 8); // invokes specialized template
	B.resize(256, 1);
	B(23, 0) = true;
	
	return 0;
}
