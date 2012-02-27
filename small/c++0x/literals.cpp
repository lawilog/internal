#include <iostream>
#include <vector>
#include <complex>
using namespace std;

long double operator "min" (long double t)
{
	return 60 * t;
}

long double operator"" h(long double t)
{
	return 60 * 60 * t;
}

constexpr complex<long double> operator "" _i(long double d) // cooked form
{ 
    return complex<long double>(0, d); 
}

int main()
{
	double start = 13h + 30min;
	double ende  = 14h + 45min;
	cout<< (ende - start) <<endl;
	
	auto val = 3.14_i;
	
	return 0;
}
