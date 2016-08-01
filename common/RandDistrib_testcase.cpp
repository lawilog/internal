#include <iostream>
#include "RandDistrib.hpp"
#include "vaout.hpp"
using namespace std;
using namespace LW;

int main()
{
	RandDistrib<double, uniform_real_distribution> myrand(4, 7);
	cout<< myrand() <<endl;
	cout<< myrand.F.max() <<endl;
	
	RandDistrib<float, normal_distribution> randn(0, 1);
	cout<< randn() <<endl;
	cout<< randn.F.stddev() <<endl;
	
	RandDistrib<int, binomial_distribution> binomi(9, 0.4);
	cout<< binomi() <<endl;
	cout<< binomi.F.min() <<endl;
	
	RandDistrib<double, uniform_real_distribution> randv(0, 1);
	valarray<double> v = 2.0 * randv(10) - 1.0;
	cout<< v << endl;
	
	return 0;
}
	
