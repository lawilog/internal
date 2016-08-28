#include <iostream>
#include "vector3d.hpp"
using namespace std;
using namespace LW;

int main(int argc, char** argv)
{
	vector3d<int> a(2, 3, 5);
	array<size_t,3> N = a.size();
	for(unsigned i = 0; i < N[0]; ++i)
		for(unsigned j = 0; j < N[1]; ++j)
			for(unsigned k = 0; k < N[2]; ++k)
				a(i, j, k) = 100*i + 10*j + k;
	
	a.resize(33, 1, 1);
	for(unsigned m = 0; m < 33; ++m)
		cout<< a.at(m, 0, 0) <<endl;
	
	cout<<"Good. Now the following should throw an error:"<<endl;
	a.resize(5, 3, 2);
	cout<< a(1, 2, 3) <<endl; // works, because there are enough elements
	cout<< a.at(1, 2, 3) <<endl; // but 3 > 2!
	
	return 0;
}
