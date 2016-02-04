#include <stdio.h>
#include <stdlib.h>

#ifndef uint64_t
typedef unsigned long long uint64_t;
#endif

struct thread_data
{
	double** data_chunks;
	uint64_t** ind_chunks;
	double h;
	uint64_t my_start_ind;
	uint64_t my_end_ind;
	double sum;
};

const unsigned max_chunks = 2700;
const unsigned chunks_size = 104857600 / (sizeof(double) + sizeof(uint64_t)); // 104857600 = 100MB

void thread_init(struct thread_data* data)
{
	uint64_t chunk, elemt;
	for(uint64_t i = my_start_ind; i < my_end_ind; ++i)
	{
		chunk = i / chunks_size;
		elemt = i % chunks_size;
		ind_chunks[chunk][elemt] = i;
		data_chunks[chunk][elemt] = i*h;
	}
}

void thread_run(struct thread_data* data)
{
	
}

int main(int argc, char** argv)
{
	if(argc < 4)
	{
		printf("usage: %s N TotalMem AccessDisorder FloatIntensity\n"
			"N:              [integer] number of threads\n"
			"TotalMem:       [integer] RAM in multiples of 100MB, <= %u\n"
			"FloatIntensity: [integer] the greater this number, the more operations per memory\n"
			"AccessDisorder: [float] \"random\" access parameter. from 0 = ordered to 1 = disordered\n", argv[0], 2700);
		return 1;
	}
	const unsigned n_threads = atoi(argv[1]);
	const unsigned n_chunks  = atoi(argv[2]);
	const unsigned n_ops     = atoi(argv[3]);
	const double f_shuffle  = atof(argv[4]);
	
	if(n_chunks > max_chunks)
	{
		printf("TotalMem must be <= %u\n", max_chunks);
		return 1;
	}
	
	const uint64_t n_elements = n_chunks * chunks_size;
	const uint64_t n_shuffle = (uint64_t)(n_elements * f_shuffle);
	const double h = 1.0 / (n_elements - 1);
	
	double* data_chunks[max_chunks]; // static array of pointers
	uint64_t* ind_chunks[max_chunks];
	for(unsigned c = 0; c < n_chunks; ++c)
	{
		data_chunks[c] = (double*) malloc(sizeof(double) * chunks_size);
		ind_chunks[c]  = (uint64_t*) malloc(sizeof(uint64_t) * chunks_size);
	}
	
	thread_data* thread_dats = (thread_data*) malloc(sizeof(thread_data) * n_threads);
	for(unsigned t = 1; t < n_threads; ++t)
	{
		thread_dats[t].data_chunks = data_chunks;
		thread_dats[t].ind_chunks = ind_chunks;
		thread_dats[t].h = h;
		thread_dats[t].my_start_ind = 23;
		thread_dats[t].my_end_ind = 42;
		thread_dats[t].sum = 0.0;		
	}
	
	for(unsigned t = 1; t < n_threads; ++t)
		thread_init(& thread_dats[i]);
	
	uint64_t chunk, elemt;
	for(uint64_t kk, k = 0, s = 0; s < n_shuffle; ++s)
	{
		chunk = i / chunks_size;
		elemt = i % chunks_size;
		ind_chunks[chunk][elemt] = i;
		data_chunks[chunk][elemt] = i*h;
		
		kk = (k + 3335777) % n_elements; // 3335777 is prime
		ind[k] = kk;
		ind[kk] = k;
		k = kk;
	}
	
	free(thread_dats);
	
	for(unsigned c = n_chunks; c > 0; --c)
	{
		free(ind_chunks[c-1]);
		free(data_chunks[c-1]);
	}
	
	const uint64_t N = argc>1 ? 1000000 * atoi(argv[1]) : 2;
	const uint64_t M = argc>2 ? (uint64_t)(N*atof(argv[2])) : 0;
	
	uint64_t* ind = (uint64_t*) malloc(sizeof(uint64_t) * N);
	double* x = (double*) malloc(sizeof(double) * N);
	uint64_t i, k, kk;
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
	
	const unsigned long N = argc>1 ? 1000000 * atoi(argv[1]) : 2;
	unsigned long n;
	float x, xx, err = 0.0;
	for(n = 1; n < N; ++n)
	{
		x = n;
		while(x > 1.5)
		{
			xx = x / 2.0;
			if(xx - (unsigned long)(xx) > 0.25 ) x = 3.0*x + 1.0;
			else x = xx;
		}
		err += x>1.0 ? 1.0-x : x-1.0;
	}
	printf("err = %e\n", err);
	
	return 0;
}

