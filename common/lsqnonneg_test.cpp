#include <iostream>
#include <Eigen/Dense>
#include <Eigen/QR>
#include "lsqnonneg.hpp"
using namespace std;
using namespace Eigen;

int main()
{
	MatrixXd C(3, 2);
	C <<
		1, 0,
		0, 1,
		2, 1;
	
	VectorXd d(3);
	d << 1, 3, -2;
	
	VectorXd x = lsqnonneg (C, d);
	cout<< x <<endl;
	
	
	
	MatrixXd A(4, 2);
	A <<
		0.0372, 0.2869,
		0.6861, 0.7071,
		0.6233, 0.6245,
		0.6344, 0.6170;
	
	VectorXd b(4);
	b << 0.8587, 0.1781, 0.0747, 0.8405;
	
	VectorXd y = lsqnonneg (A, b);
	cout<< y <<endl;
	
	return 0;
}
