#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>

//MPI sort methods
int MPI_Ranking_sort(int n, double * a, int root, MPI_Comm comm);


int main(int argc, char *argv[])
{
	int rank, size;

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

	double time1 = MPI_Wtime();
	MPI_Ranking_sort(nrElems, array, 0, MPI_COMM_WORLD);

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

int MPI_Ranking_sort(int n, double* a, int root, MPI_Comm comm)
{
	int rank, size;
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);

	int *ranking = (int*)calloc(n / size, sizeof(int));
	int *overallRanking = (int*)calloc(n, sizeof(int));

	MPI_Bcast(&a[0], n, MPI_DOUBLE, root, comm);

	for (int i = 0; i < n / size; i++)
	{
		ranking[i] = 0;
		for (int j = 0; j < n; j++)
		{
			if (a[i + rank * n / size] > a[j])
			{
				ranking[i]++;
			}
		}
	}

	MPI_Gather(ranking, n / size, MPI_INT, overallRanking, n / size, MPI_INT, root, comm);

	if (rank == 0)
	{
		double *tmp = (double*)calloc(n, sizeof(double));
		for (int i = 0; i < n; i++)
		{
			tmp[overallRanking[i]] = a[i];
		}

		for (int i = 0; i < n; i++)
		{
			a[i] = tmp[i];
		}
	}

	return MPI_SUCCESS;
}