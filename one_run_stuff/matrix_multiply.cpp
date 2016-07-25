#include <iostream>
#include <ctime>
#include "RandDistrib.hpp"
using namespace std;
using namespace LW;

int main()
{
	RandDistrib<double, uniform_real_distribution> rand(0, 1);
	unsigned N; cin >> N;
	
	clock_t tic = clock();
	const unsigned NN = N*N;
	double* A = new double[NN]; // A[i,j] = A[N*i+j]
	for(unsigned i = 0; i < NN; ++i)
		A[i] = rand();
	
	cout<<"Elapsed time is "<< (double)(clock()-tic)/CLOCKS_PER_SEC <<" seconds."<<endl;

	tic = clock();
	double* B = new double[NN]; // B[i,j] = sum_k A[i,k] * A[k,j]
	for(unsigned i = 0; i < N; ++i)
	{
		for(unsigned j = 0; j < N; ++j)
		{
			double b = 0;
			for(unsigned k = 0; k < N; ++k)
				b += A[N*i+k] * A[N*k+j];
			
			B[N*i+j] = b;
		}
	}
	cout<<"Elapsed time is "<< (double)(clock()-tic)/CLOCKS_PER_SEC <<" seconds."<<endl;
	
	delete [] B;
	delete [] A;
	return 0;
}

