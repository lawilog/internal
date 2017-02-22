#include "power.hpp"
using namespace LW;

double hoch12_a(const double& x)
{
	double y = x * x; // yields x^2
	y *= x; // yields x^3
	y *= y; // yields x^6
	y *= y; // yields x^12
	return y;
}

/*
y_12 = {
	y_6 = {
		y_3 = {
			y_1 = {
				y_0 = 1
				y2_0 = 1
				even_0 = true
				positive_0 = false
				return y2_0; // == 1
			}
			y2_1 = y_1 * y_1; // 1
			even_1 = false
			positive_1 = true
			return x * y2_1; // == x
		}
		y2_3 = y_3 * y_3; // x^2
		even_3 = false
		positive_3 = true
		return x * y2_3; // x^3
	}
	y2_6 = y_6 * y_6; // x^6
	even_6 = true
	positive_6 = true
	return y2_6; // x^6
}
y2_12 = y_12 * y_12; // x^12
even_12 = true
positive_12 = true
return y2_12; // x^12
*/

double hoch12_b(const double& x)
{
	return power<12>(x);
}

double hoch12_c(const double& x)
{
	return power_<12,double,true,true>::of(x);
}
