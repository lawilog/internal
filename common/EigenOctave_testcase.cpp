#include <iostream>
#include "EigenOctave.hpp"
using namespace std;
using namespace Eigen;

int main()
{
	VectorXd z(10);
	z << 7, 4, 2, 8, 1, 3, 6, 0, 9, 5;
	cout<<"z = ["<< z.transpose() <<"]\n"<<endl;
	
	VectorXi p = find( z.array() > 6 );
	cout<<"p = z>6 = ["<< p.transpose() << "]\n"<<endl;
	
	VectorXd y = pick(z, p);
	cout<<"z(p) = ["<< y.transpose() <<"]\n"<<endl;
	
	z = remove(z, p);
	cout<<"z(p) = []; z = ["<< z.transpose() <<"]\n"<<endl;
	
	VectorXd a(10);
	a << 10, 20, 30, 40, 50, 60, 70, 80, 90, 100;
	cout<<"a = ["<< a.transpose() <<"]\n"<<endl;
	
	VectorXi ind(3);
	ind << 0, 4, 5;
	cout<<"ind = ["<< ind.transpose() <<"]\n"<<endl;
	
	cout<<"a(ind) = []; a = ["<< remove(a, ind).transpose() <<"]\n"<<endl;
	
	MatrixXd M(3, 3);
	M <<
		11, 12, 13,
		21, 22, 23,
		31, 32, 33;
	
	cout<<"M = \n"<< M <<endl;
	
	VectorXi c(2); c<< 0, 2;
	cout<<"M(:, [1, 3]) = \n"<< pick_col(M, c) <<endl;
	cout<<"M([1, 3], :) = \n"<< pick_row(M, c) <<endl;
	
	cout<<"a = ["<< a.transpose() <<"]\n"<<endl;
	cout<<"Crash test:"<<endl;
	try
	{
		ind(0) = -1;
		ind(1) = 0;
		ind(2) = 3;
		VectorXd b = remove(a, ind);
	}
	catch (const std::exception& e)
	{
		cout<<"Caught expection: \""<< e.what() <<"\"."<<endl;
    }
	
	try
	{
		ind(0) = 3;
		ind(1) = 2;
		ind(2) = 1;
		VectorXd b = remove(a, ind);
	}
	catch (const std::exception& e)
	{
		cout<<"Caught expection: \""<< e.what() <<"\"."<<endl;
    }
	
	return 0;
}
