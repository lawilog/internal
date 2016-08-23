#include <iostream>
#include "power.hpp"
using namespace std;
using namespace LW;

int main()
{
	cout<<"2^3 = "<< power<3>(2) <<endl;
	cout<<"0^0 = "<< power<0>(0) <<endl;
	cout<<"1^-1 = "<< power<-1>(1.0) <<endl;
	cout<<"-1^1 = "<< power<1>(-1) <<endl;
	cout<<"2^-2 = "<< power<-2>(2.0) <<endl;
	double x; cin >> x;
	float y; cin >> y;
	cout<< x << "^12 = "<< power<12>(x) <<endl;
	cout<< y << "^-42 = "<< power<-42>(y) <<endl;
	return 0;
}
