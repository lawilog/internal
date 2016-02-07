#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	double f_shuffle;
	double sum;
};
typedef struct thread_data thread_data;

const unsigned max_chunks = 2700;
const unsigned chunks_size = 104857600 / (sizeof(double) + sizeof(uint64_t)); // 104857600 = 100MB

void thread_init(struct thread_data* data)
{
	uint64_t chunk, elemt;
	for(uint64_t i = data->my_start_ind; i < data->my_end_ind; ++i)
	{
		chunk = i / chunks_size;
		elemt = i % chunks_size;
		data->ind_chunks[chunk][elemt] = i;
		data->data_chunks[chunk][elemt] = i * data->h;
	}
	
	const uint64_t n_thread_elements = data->my_end_ind - data->my_start_ind;
	const uint64_t n_shuffle = (uint64_t)(n_thread_elements * data->f_shuffle);
	uint64_t chunk2, elemt2;
	for(uint64_t kk, k = 0, s = 0; s < n_shuffle; ++s)
	{
		kk = data->my_start_ind + (k + 3335777) % n_thread_elements; // 3335777 is prime
		chunk = k / chunks_size;
		elemt = k % chunks_size;
		chunk2 = kk / chunks_size;
		elemt2 = kk % chunks_size;
		data->ind_chunks[chunk][elemt]   = kk;
		data->ind_chunks[chunk2][elemt2] = k;
		k = kk;
	}
}

void thread_run(struct thread_data* data)
{
	double xi;
	uint64_t chunk, elemt, ind;
	for(uint64_t i = data->my_start_ind; i < data->my_end_ind; ++i)
	{
		chunk = i / chunks_size;
		elemt = i % chunks_size;
		ind = data->ind_chunks[chunk][elemt];
		chunk = ind / chunks_size;
		elemt = ind % chunks_size;
		xi = data->data_chunks[chunk][elemt];
		data->sum += xi * xi;
	}
	
	// TODO compute more
	/*unsigned long n;
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
	printf("err = %e\n", err);*/
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
	const unsigned n_chunks  = atoi(argv[2]);
	const unsigned n_ops     = atoi(argv[3]);
	const double f_shuffle   = atof(argv[4]);
	if(n_chunks > max_chunks)
	{
		printf("TotalMem must be <= %u\n", max_chunks);
		return 1;
	}
	printf("%u threads, %4.1f GB, calc %u, disorder %f\n", n_threads, 0.1*n_chunks, n_ops, f_shuffle);
	
	clock_t t0 = clock(), t1, t2;
	
	// alloc memory and init data structures
	const uint64_t n_elements = n_chunks * chunks_size;
	const uint64_t elements_per_thread = n_elements / n_threads;
	const double h = 1.0 / (n_elements - 1);
	double* data_chunks[max_chunks]; // static array of pointers
	uint64_t* ind_chunks[max_chunks];
	for(unsigned c = 0; c < n_chunks; ++c)
	{
		data_chunks[c] = (double*) malloc(sizeof(double) * chunks_size);
		ind_chunks[c]  = (uint64_t*) malloc(sizeof(uint64_t) * chunks_size);
	}
	uint64_t ind = 0;
	thread_data* thread_dats = (thread_data*) malloc(sizeof(thread_data) * n_threads);
	for(unsigned t = 0; t < n_threads; ++t)
	{
		thread_dats[t].data_chunks = data_chunks;
		thread_dats[t].ind_chunks = ind_chunks;
		thread_dats[t].h = h;
		thread_dats[t].my_start_ind = ind; ind += elements_per_thread;
		thread_dats[t].my_end_ind   = ind; ++ind;
		thread_dats[t].f_shuffle = f_shuffle;
		thread_dats[t].sum = 0.0;
		// printf("Thread %u from %llu to %llu.\n", t, thread_dats[t].my_start_ind, thread_dats[t].my_end_ind);
	}
	thread_dats[n_threads-1].my_end_ind = n_elements;
	
	// TODO: really start threads
	
	// init data
	for(unsigned t = 0; t < n_threads; ++t)
		thread_init(& thread_dats[t]);
	
	t1 = clock();
	
	// perform calculation
	printf("Integrating... ");
	for(unsigned t = 0; t < n_threads; ++t)
		thread_run(& thread_dats[t]);
	
	double s = 0.0;
	for(unsigned t = 0; t < n_threads; ++t)
		s += thread_dats[t].sum;
	s /= n_elements;
	printf("%20.16f\n", s);
	
	t2 = clock();
	
	// free memory
	free(thread_dats);
	for(unsigned c = n_chunks; c > 0; --c)
	{
		free(ind_chunks[c-1]);
		free(data_chunks[c-1]);
	}
	
	printf("Time init: %10.3f, calc: %10.3f\n", (double)(t1-t0)/CLOCKS_PER_SEC, (double)(t2-t1)/CLOCKS_PER_SEC);
	
	return 0;
}
