#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
// #include <linux/vmalloc.h>
#define vmalloc malloc

#ifndef uint64_t
typedef unsigned long long uint64_t;
#endif

struct thread_data
{
	double* X;
	uint64_t* ind;
	double h;
	double f_shuffle;
	unsigned n_ops;
	uint64_t my_start_ind;
	uint64_t my_end_ind;
	double sum;
};
typedef struct thread_data thread_data;

void* thread_init(void* vdata)
{
	thread_data* const data = (thread_data*) vdata;
	double* const X = data -> X;
	uint64_t* const ind = data -> ind;
	const double h = data->h;
	const uint64_t my_start_ind = data -> my_start_ind;
	const uint64_t my_end_ind = data -> my_end_ind;
	const uint64_t n_thread_elements = my_end_ind - my_start_ind;
	const uint64_t n_shuffle = (uint64_t)(n_thread_elements * data->f_shuffle);
	for(uint64_t i = my_start_ind; i < my_end_ind; ++i)
	{
		ind[i] = i;
		X[i] = i * h;
	}
	for(uint64_t kk, k = 0, s = 0; s < n_shuffle; ++s)
	{
		kk = my_start_ind + (k + 3335777) % n_thread_elements; // 3335777 is prime
		ind[k]  = kk;
		ind[kk] = k;
		k = kk;
	}
	return NULL;
}

void* thread_run(void* vdata)
{
	thread_data* const data = (thread_data*) vdata;
	double* const X = data -> X;
	uint64_t* const ind = data -> ind;
	const unsigned n_ops = data -> n_ops;
	const uint64_t my_start_ind = data -> my_start_ind;
	const uint64_t my_end_ind = data -> my_end_ind;
	double* const sum = & data->sum;
	for(uint64_t i = my_start_ind; i < my_end_ind; ++i)
	{
		const double xi = X[ind[i]];
		double d = 0.0;
		for(unsigned n = 1; n < n_ops; ++n)
		{
			double x = n;
			while(x > 1.5)
			{
				const double xx = x / 2.0;
				x = (xx - (unsigned long)(xx) > 0.25 ) ? 3.0*x + 1.0 : xx;
			}
			d += x - 1.0;
		}
		*sum += xi * xi + d;
	}
	return NULL;
}

int main(int argc, char** argv)
{
	// parse input
	if(argc < 4)
	{
		printf("usage: %s N TotalMem AccessDisorder FloatIntensity\n"
			"N:              [integer] number of threads\n"
			"TotalMem:       [integer] RAM in multiples of 100MB, <= %u\n"
			"CalcIntensity:  [integer] the greater this number, the more operations per memory\n"
			"AccessDisorder: [float] \"random\" access parameter. from 0 = ordered to 1 = disordered\n", argv[0], 2700);
		return 1;
	}
	const unsigned n_threads = atoi(argv[1]);
	const uint64_t n_mem     = atoi(argv[2]);
	const unsigned n_ops     = atoi(argv[3]);
	const double f_shuffle   = atof(argv[4]);
	printf("%u threads, %4.1f GB total mem, %u calc, %3.2f%% disorder\n", n_threads, 0.1*n_mem, n_ops, 100*f_shuffle);
	
	// alloc memory and init data structures
	clock_t t0 = clock(), t1, t2, t3;
	const uint64_t n_elements = n_mem * 104857600 / (sizeof(double) + sizeof(uint64_t)); // 104857600 == 100MiB
	const uint64_t elements_per_thread = n_elements / n_threads;
	const double h = 1.0 / (n_elements - 1);
	double* const X = (double*) vmalloc(sizeof(double) * n_elements);
	uint64_t* const ind = (uint64_t*) vmalloc(sizeof(uint64_t) * n_elements);
	pthread_t* const pthreads = (pthread_t*) malloc(sizeof(pthread_t) * n_threads);
	thread_data* const thread_dats = (thread_data*) malloc(sizeof(thread_data) * n_threads);
	if(!X || !ind || !pthreads || !thread_dats)
	{
		printf("ERROR: Failed to allocate enough memory.\n");
		return 1;
	}
	uint64_t pos = 0;
	for(unsigned t = 0; t < n_threads; ++t)
	{
		thread_dats[t].X = X;
		thread_dats[t].ind = ind;
		thread_dats[t].h = h;
		thread_dats[t].f_shuffle = f_shuffle;
		thread_dats[t].n_ops = n_ops;
		thread_dats[t].my_start_ind = pos; pos += elements_per_thread;
		thread_dats[t].my_end_ind   = pos; ++pos;
		thread_dats[t].sum = 0.0;
	}
	thread_dats[n_threads-1].my_end_ind = n_elements;
	
	// init data
	for(unsigned t = 0; t < n_threads; ++t)
		pthread_create(&pthreads[t], NULL, thread_init, & thread_dats[t]);
	
	for(unsigned t = 0; t < n_threads; ++t)
		pthread_join(pthreads[t], NULL);
	
	t1 = clock();
	
	// perform calculation
	printf("Integrating... ");
	t2 = clock();
	for(unsigned t = 0; t < n_threads; ++t)
		pthread_create(&pthreads[t], NULL, thread_run, & thread_dats[t]);
	
	for(unsigned t = 0; t < n_threads; ++t)
		pthread_join(pthreads[t], NULL);
	
	double s = 0.0;
	for(unsigned t = 0; t < n_threads; ++t)
		s += thread_dats[t].sum;
	s = h * (s - 0.5);
	t3 = clock();
	printf("%20.16f\n", s);
	printf("avg time per thread: %10.3f init, %10.3f calc\n", (double)(t1-t0)/CLOCKS_PER_SEC/n_threads, (double)(t3-t2)/CLOCKS_PER_SEC/n_threads);
	
	// free memory
	free(thread_dats);
	free(pthreads);
	free(ind);
	free(X);
	return 0;
}
