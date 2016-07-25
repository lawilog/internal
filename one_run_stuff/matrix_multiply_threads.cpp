#include <iostream>
#include <ctime>
#include <thread>
#include <vector>
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
	vector<thread> threads;
	for(unsigned ij = 0; ij < NN; ++ij)
	{
		threads.push_back(thread([ij,&rand,&A](){
			A[ij] = rand();
		}));
	}
	for(auto& thread: threads)  thread.join();
	cout<<"Elapsed time is "<< (double)(clock()-tic)/CLOCKS_PER_SEC <<" seconds."<<endl;

	tic = clock();
	vector<thread> threads2;
	double* B = new double[NN]; // B[i,j] = sum_k A[i,k] * A[k,j]
	for(unsigned i = 0; i < N; ++i)
	{
		for(unsigned j = 0; j < N; ++j)
		{
			threads2.push_back(thread([i,j,&A,&B,&N](){
				double b = 0;
				for(unsigned k = 0; k < N; ++k)
					b += A[N*i+k] * A[N*k+j];
			
				B[N*i+j] = b;
			}));
		}
	}
	for(auto& thread: threads2)  thread.join();
	cout<<"Elapsed time is "<< (double)(clock()-tic)/CLOCKS_PER_SEC <<" seconds."<<endl;
	
	delete [] B;
	delete [] A;
	return 0;
}

