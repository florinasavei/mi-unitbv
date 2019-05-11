#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>


//MPI sort methods
int MPI_Bucket_sort(int n, double m, double *a, int root, MPI_Comm comm);
//helper methods
int compare(const void * a, const void * b);

int main(int argc, char *argv[])
{
	int rank, size;
	//find rank size
	const int nrElems = 1000000;
	const double m = 200.0;

	// Init + rank + size
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	double* array = (double *)calloc(nrElems, sizeof(double));

	if (rank == 0)
	{
		//initialise the array with random values, then scatter to all processors
		srand(((unsigned)time(NULL) + rank));

		for (int i = 0; i < nrElems; i++)
		{
			array[i] = ((double)rand() / RAND_MAX)*m;
		}

	}

	//print the unsorted array
	if (nrElems <= 12)
	{
		if (rank == 0)
		{
			printf("\nUnsorted array:\n");
			for (int i = 0; i < nrElems; i++)printf("%lf ", array[i]);
			printf("\n\n");
		}
	}

	const double time1 = MPI_Wtime();

	MPI_Bucket_sort(nrElems, m, array, 0, MPI_COMM_WORLD);

	if (nrElems > 12)
	{
		printf("Processor %d worked for %lf\n", rank, MPI_Wtime() - time1);
	}

	//print the sorted array
	if (nrElems <= 12)
	{
		if (rank == 0)
		{
			printf("\nSorted array:\n");
			for (int i = 0; i < nrElems; i++)printf("%lf ", array[i]);
			printf("\n\n");
		}
	}

	MPI_Finalize();

}

int MPI_Bucket_sort(int n, double m, double *a, int root, MPI_Comm comm)
{

	int rank, size, count = 0;
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);
	int *counters = (int *)calloc(size, sizeof(int));
	int *displacements = (int*)calloc(size, sizeof(int));

	double * bucket = (double*)calloc(n, sizeof(double));

	MPI_Bcast(&a[0], n, MPI_DOUBLE, root, comm);

	for (int i = 0; i < n; i++)
	{
		if (rank*m / size <= a[i] && a[i] < (rank + 1)*m / size)
		{
			bucket[count++] = a[i];
		}
	}

	qsort(bucket, count, sizeof(double), compare);

	MPI_Gather(&count, 1, MPI_INT, counters, 1, MPI_INT, root, comm);

	//create displacement array
	displacements[0] = 0;
	for (int i = 0; i < size - 1; i++)
	{
		displacements[i + 1] = displacements[i] + counters[i];
	}

	MPI_Gatherv(bucket, count, MPI_DOUBLE, a, counters, displacements, MPI_DOUBLE, root, comm);

	return MPI_SUCCESS;

}

int compare(const void * a, const void * b)
{
	if ((*(double*)a > *(double*)b))
	{
		return 1;

	}
	else if ((*(double*)a < *(double*)b))
	{
		return -1;
	}

	return 0;
}