#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <forward_list>
#include <string>
#include "sum.hpp"
using namespace std;
using namespace LW;

int main(int argc, char** argv)
{
	vector<int> v(111, 7);
	int s = sum(v.begin(), v.end());
	cout<<"s = "<< s <<endl;
	cout<<"sum(v) = "<< sum(v) <<endl;
	
	
	const unsigned N = 5;
	float a[N];
	for(unsigned i = 0; i < N; ++i)
		a[i] = 2*i+1;
	
	float x = sum(a, a+N);
	cout<<"x = "<< x <<endl;
	cout<<"sum of C array: "<< sum(a) <<endl;
	
	array<double,6> A;
	A.fill(7);
	cout<<"sum of std::array : "<< sum(A.begin(), A.end()) <<endl;
	
	forward_list<int> L = {0, 1, 1, 1, 3, 3};
	L.unique();
	cout<<"sum of std::forward_list : "<< sum(L.begin(), L.end()) <<endl;
	
	vector<string> w = {"Hello", " ", "world"};
	string ws = sum(w);
	cout<<"sum of std::string : "<< ws <<endl;
	
	double y[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
	cout<<"trying this hack: "<< sum(reinterpret_cast<array<double, sizeof(y)/sizeof(double)>&>(y) ) <<endl;
	
	vector<double> B(7, 0.1);
	cout<< accumulate(B.begin(), B.end(), 0) << endl; // warning: this is 0.
	cout<< accumulate(B.begin(), B.end(), 0.0) << endl; // this is okay.
	
	unsigned M = argc > 1 ? atoi(argv[1]) : 3;
	int* ia = new int[M];
	// cout<<"sum of pointer? : "<< sum(ia) <<endl; // does not compile because N size of N is not known on compile time
	cout<<"sum of array: "<< sum(ia, ia+M) <<endl;
	delete [] ia;
	
	return 0;
}
