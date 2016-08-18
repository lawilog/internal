#include <iostream>
#include "arraynd.hpp"
using namespace std;
using namespace LW;

int main()
{
	arraynd<int,2> a({3,4});
	cout<<"a length = "<< (a.flat_end() - a.flat_begin()) << endl;
	for(unsigned i = 0; i < 3; ++i)
		for(unsigned j = 0; j < 4; ++j)
			a(i,j) = 10*i + j;
	
	arraynd<int,2> b = a;
	
	a.resize({1, 15});
	for(unsigned k = 0; k < 15; ++k)
		cout<< a.at(0, k) <<endl;
	
	
	
	arraynd<int,3> A({2, 3, 5});
	array<size_t,3> N = A.size();
	for(unsigned i = 0; i < N[0]; ++i)
		for(unsigned j = 0; j < N[1]; ++j)
			for(unsigned k = 0; k < N[2]; ++k)
				A(i, j, k) = 100*i + 10*j + k;
	
	A.resize({33, 1, 1});
	for(unsigned m = 0; m < 33; ++m)
		cout<< A.at(m, 0, 0) <<endl;
	
	cout<<"Good. Now the following should throw an error:"<<endl;
	A.resize({5, 3, 2});
	try
	{
		cout<< A(1, 2, 3) <<endl; // works, because there are enough elements
		cout<< A.at(1, 2, 3) <<endl; // but 3 > 2!
		cout<<"If this line is printed, something went wrong."<<endl;
	}
	catch(const out_of_range& e)
	{
		cout<<"As expected, an error occured: "<< e.what() <<endl;
	}
	catch(...) {throw;}
	
	// does not compile du to wrong number of indices:
	// A(), A(3), A(9,8,7,6,5,4)
	
	cout<<"Over and out."<<endl;
	
	return 0;
}
