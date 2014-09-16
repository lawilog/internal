#include <iostream>
#include <Eigen/Dense>
#include "lscov.hpp"
using namespace std;
using namespace Eigen;

int main()
{
	MatrixXd A(3, 2);
	A <<
		1, 1,
		2, 1,
		3, 1;
	
	VectorXd b(3);
	b << 17, 20, 37;
	
	MatrixXd V(3, 3);
	V <<
		1/0.45, 0,     0,
		0,      1/0.1, 0,
		0,      0,     1/0.45;
	
	VectorXd x = lscov(A, b, V);
	cout<< x <<endl;
	
	VectorXd w(3);
	w << 0.45, 0.1, 0.45;
	
	cout<<"with w: "<< lscov(A, b, w) <<endl;
	
	
	MatrixXd M(4, 2);
	M <<
		1, 0,
		1, 1,
		1, 2,
		1, 3;
	
	VectorXd k(4);
	k << -1, 9, 666, 29;
	
	VectorXd ww(4);
	ww << 1, 1, 0.01, 1;
	
	cout<<"with 1s: "<< lscov(M, k, VectorXd(VectorXd::Ones(M.rows()))) <<endl;
	cout<<"with ww: "<< lscov(M, k, ww) <<endl;
	
	return 0;
}
