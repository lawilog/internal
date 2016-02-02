#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	const int mpi_root = 0;
	int numnodes, myid, mpi_err;
	
	mpi_err = MPI_Init(&argc, &argv);
	mpi_err = MPI_Comm_size(MPI_COMM_WORLD, &numnodes);
	mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	const int count = 4;
	int i;
	int* send_ray;
	if(myid == mpi_root)
	{
		const int size = count * numnodes;
		send_ray = (int*) malloc(size * sizeof(int));
		for(i = 0; i < size; ++i)
			send_ray[i] = i;
	}
	
	int* myray = (int*) malloc(count * sizeof(int));
	mpi_err = MPI_Scatter(send_ray, count, MPI_INT, myray, count, MPI_INT, mpi_root, MPI_COMM_WORLD);
	
	int total = 0;
	for(i = 0; i < count; ++i)
	    total = total + myray[i];
	
	printf("myid= %d total= %d\n ", myid, total);
	
	int gtotal;
	mpi_err = MPI_Reduce(&total, &gtotal, 1, MPI_INT, MPI_SUM, mpi_root, MPI_COMM_WORLD);
	
	if(myid == mpi_root)
	  printf("results from all processors= %d \n ", gtotal);
	
	mpi_err = MPI_Finalize();
}
