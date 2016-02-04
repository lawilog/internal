#include <stdio.h>
#include <stdlib.h>

typedef unsigned long ulint;

int main(int argc, char** argv)
{
	const ulint N = argc>1 ? 1000000 * atoi(argv[1]) : 2;
	const ulint M = argc>2 ? (ulint)(N*atof(argv[2])) : 0;
	const double h = 1.0 / (N-1);
	ulint* ind = (ulint*) malloc(sizeof(ulint) * N);
	double* x = (double*) malloc(sizeof(double) * N);
	ulint i, k, kk;
	double s, xx;
	for(i = 0; i < N; ++i)
	{
		ind[i] = i;
		x[i] = i*h;
	}
	for(i = 0, k = 0; i < M; ++i)
	{
		kk = (k+3335777)%N; // 3335777 is prime
		ind[k] = kk;
		ind[kk] = k;
		k = kk;
	}
	printf("Integrating... ");
	s = 0.0;
	for(i = 0; i < N; ++i)
	{
		xx = x[ind[i]];
		s += xx * xx;
	}
	s /= N;
	printf("%20.16f\n", s);
	free(x);
	free(ind);
	return 0;
}

