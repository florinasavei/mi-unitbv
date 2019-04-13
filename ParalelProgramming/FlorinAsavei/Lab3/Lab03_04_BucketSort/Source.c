/**
 * MPI Program that performs simple sorting
 *
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>



 //MPI sort methods
int compare(const void * a, const void * b);
//int MPI_Direct_Sort(int n, double *a, int root, MPI_Comm comm);
int MPI_Ranking_sort(int n, double * a, int root, MPI_Comm comm);
int MPI_Bucket_sort(int n, double m, double *a, int root, MPI_Comm comm);
//utility methods
double * merge_array(int n, double * a, int m, double * b);
void     merge_sort(int n, double * a);
void     swap(double * a, double * b);

int main(int argc, char *argv[])
{

	int rank, size;

	int n = 100000, i, j, k, x, q, l, shell, pair, *nr;
	double m = 200.0;
	double * scattered_array, *array = NULL;

	// Init + rank + size
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	array = (double *)calloc(n, sizeof(double));

	if (rank == 0)
	{

		//initialise the array with random values, then scatter to all processors
		srand(((unsigned)time(NULL) + rank));

		for (i = 0; i < n; i++)
		{
			array[i] = ((double)rand() / RAND_MAX)*m;
		}

	}

	/*printf("\nunsorted: \n");

	if (rank == 0)
	{
		for (int i = 0; i < n; i++)printf("%lf ", array[i]);
	}*/


	double time1 = MPI_Wtime();
	//MPI_Direct_Sort(n, array, 0, MPI_COMM_WORLD);
	//MPI_Ranking_sort(n, array, 0, MPI_COMM_WORLD);
	MPI_Bucket_sort(n, m, array, 0, MPI_COMM_WORLD);

	//printf("\nsorted: \n");
	printf("\nProcessor %d worked for %lf\n", rank, MPI_Wtime() - time1);

	//if (rank == 0)
	//{
	//	for (int i = 0; i < n; i++)printf("%lf ", array[i]);
	//}

	MPI_Finalize();

}

int MPI_Ranking_sort(int n, double * a, int root, MPI_Comm comm)
{
	int rank, size;
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);

	int * ranking = (int *)calloc(n / size, sizeof(int));
	int *overallRanking = (int *)calloc(n, sizeof(int));

	MPI_Bcast(&a[0], n, MPI_DOUBLE, root, comm);

	for (int i = 0; i < n / size; i++)
	{
		ranking[i] = 0;
		for (int j = 0; j < n; j++)
		{
			if (a[i + rank * n / size] > a[j])
				ranking[i]++;
		}
	}

	MPI_Gather(ranking, n / size, MPI_INT, overallRanking, n / size, MPI_INT, root, comm);

	if (rank == 0)
	{
		double *tmp = (double *)calloc(n, sizeof(double));
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

int MPI_Bucket_sort(int n, double m, double *a, int root, MPI_Comm comm)
{

	int rank, size, count=0;
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);
	int *counters = (int *)calloc(size, sizeof(int));
	int *displacements = (int*)calloc(size, sizeof(int));

	double * bucket = (double*)calloc(n, sizeof(double));

	MPI_Bcast(&a[0], n, MPI_DOUBLE, root, comm);

	for(int i=0; i<n; i++)
	{
		if(rank*m/size<=a[i] && a[i]<(rank+1)*m/size)
		{
			bucket[count++] = a[i];
		}
	}

	qsort(bucket, count, sizeof(double), compare);

	MPI_Gather(&count, 1, MPI_INT, counters, 1, MPI_INT, root, comm);

	//create displacement array
	displacements[0] = 0;
	for(int i = 0; i<size-1; i++)
	{
		displacements[i + 1] = displacements[i] + counters[i];
	}

	MPI_Gatherv(bucket, count, MPI_DOUBLE, a, counters, displacements, MPI_DOUBLE, root, comm);

	return MPI_SUCCESS;

}

int compare(const void * a, const void * b)
{
	if( (*(double*)a > *(double*)b))
	{
		return 1;

	}else if((*(double*)a < *(double*)b))
	{
			return -1;
	}

	return 0;
}