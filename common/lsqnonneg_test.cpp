#include <iostream>
#include <Eigen/Dense>
#include <Eigen/QR>
#include "lsqnonneg.hpp"
#include "lsq_weigh_nonneg.hpp"
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
	cout<<"result x ="<< x <<endl;
	
	VectorXd xx = lsq_weigh_nonneg(C, d);
	cout<<"result xx ="<< xx <<endl;
	cout<<"err: "<< lsq_weigh_nonneg_err(C, d, xx) <<endl;
	
	
	MatrixXd A(4, 2);
	A <<
		0.0372, 0.2869,
		0.6861, 0.7071,
		0.6233, 0.6245,
		0.6344, 0.6170;
	
	VectorXd b(4);
	b << 0.8587, 0.1781, 0.0747, 0.8405;
	
	VectorXd y = lsqnonneg (A, b);
	cout<<"result y ="<< y <<endl;
	
	VectorXd yy = lsq_weigh_nonneg(A, b);
	cout<<"result yy ="<< yy <<endl;
	cout<<"err: "<< lsq_weigh_nonneg_err(A, b, yy) <<endl;
	cout<<"err: "<< lsq_weigh_nonneg_err(A, b, VectorXd::Ones(A.rows()), yy) <<endl;
	
	
	MatrixXd M(4, 2);
	M <<
		1, 0,
		1, 1,
		1, 2,
		1, 3;
	
	VectorXd g(4);
	g << 3, 13, 23, 33;
	
	cout<<"result z ="<< lsqnonneg(M, g) <<endl;
	VectorXd zz = lsq_weigh_nonneg(M, g);
	
	cout<<"result zz ="<< zz <<endl;
	cout<<"zz err: "<< lsq_weigh_nonneg_err(M, g, zz) <<endl;
	
	
	MatrixXd B(4, 3);
	B <<
		1, 0, 0,
		1, 1, 1,
		1, 2, 4,
		1, 3, 9;
	
	VectorXd h(4); // 100 + x + 0.01 * x^2
	h << 1.0e-4, 1.0101e-4, 1.0204e-4, 1.0309e-4;
	
	VectorXd vv = lsq_weigh_nonneg(B, h);
	cout<<"result vv ="<< vv <<endl;
	cout<<"err: "<< lsq_weigh_nonneg_err(B, h, vv) <<endl;
	
	
	VectorXd k(4);
	k << -1, 9, 66, 29;
	
	VectorXd w(4);
	w << 1, 1, 0.01, 1;
	
	cout<<"result lsqnonneg ="<< lsqnonneg(M, k) <<endl;
	cout<<"result lsq_weigh_nonneg ="<< lsq_weigh_nonneg(M, k) <<endl;
	cout<<"result weighted ="<< lsq_weigh_nonneg(M, k, w) <<endl;
	
	return 0;
}
