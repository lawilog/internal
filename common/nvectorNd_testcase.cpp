#include <iostream>
#include <vector>
#include <array>
#include "nvectorNd.hpp"
using namespace std;
using namespace LW;

int main()
{
	nvectorNd<double,3> v(5, 7, 8);
	v[1][2][3] = 4.0;
	cout<<"Should be four: "<< v(1,2,3) <<endl;
	std::vector<std::vector<double> >& y = v[0];
	++y[0][0];
	cout<<"Should be one: "<< v[0][0][0] <<endl;
	
	const nvectorNd<double,3> a(4, 4, 4);
	cout<<"Should be zero: "<< a(3, 2, 1) <<endl;
	
	cout<<"This should crash:"<<endl;
	v[2].at(999)[1] = 2.3;
	return 0;
}
