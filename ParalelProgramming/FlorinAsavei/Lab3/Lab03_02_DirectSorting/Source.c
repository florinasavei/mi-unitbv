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
//int compare(const void * a, const void * b);
int MPI_Direct_Sort(int n, double *a, int root, MPI_Comm comm);
//int MPI_Ranking_sort(int n, double * a, int root, MPI_Comm comm);
//int MPI_Bucket_sort(int n, double *a, int root, MPI_Comm comm);
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

	//if (rank == 0)
	//{
	//	for (int i = 0; i < n; i++)printf("%lf ", array[i]);
	//}


	double time1 = MPI_Wtime();
	MPI_Direct_Sort(n, array, 0, MPI_COMM_WORLD);
	//MPI_Ranking_sort(n, array, 0, MPI_COMM_WORLD);
	//MPI_Bucket_sort(n, array, 0, MPI_COMM_WORLD);
	printf("Processor %d worked for %lf\n", rank, MPI_Wtime() - time1);

	//if (rank == 0)
	//{
	//	for (int i = 0; i < n; i++)printf("%lf ", array[i]);
	//}

	MPI_Finalize();

}


int MPI_Direct_Sort(int n, double *a, int root, MPI_Comm comm)
{
	int rank, size;
	//find rank size
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);

	//alocate local_a

	double * local_a = (double*)calloc(n / size, sizeof(double));
	//scatter array
	MPI_Scatter(a, n / size, MPI_DOUBLE, local_a, n / size, MPI_DOUBLE, root, comm);

	//sort scattered arrays
	merge_sort(n / size, local_a);

	//gather
	MPI_Gather(local_a, n / size, MPI_DOUBLE, a, n / size, MPI_DOUBLE, root, comm);

	//processor 0 merges size-1 chunks

	if (rank == 0) {
		for (int i = 1; i < size; i++) {
			double* tmp = merge_array(i*n / size, a, n / size, a + i * n / size);
			for (int j = 0; j < (i + 1)*n / size; j++)a[j] = tmp[j];
		}
	}
	return MPI_SUCCESS;
}

// function to merge the array a with n elements with the array b with m elements
// function returns the nerged array

double * merge_array(int n, double * a, int m, double * b) {

	int i, j, k;
	double * c = (double *)calloc(n + m, sizeof(double));

	for (i = j = k = 0; (i < n) && (j < m);)

		if (a[i] <= b[j])c[k++] = a[i++];
		else c[k++] = b[j++];

	if (i == n)for (; j < m;)c[k++] = b[j++];
	else for (; i < n;)c[k++] = a[i++];

	return c;
}

// function to merge sort the array a with n elements

void merge_sort(int n, double * a) {

	double * c;
	int i;

	if (n <= 1) return;

	if (n == 2) {

		if (a[0] > a[1])swap(&a[0], &a[1]);
		return;
	}



	merge_sort(n / 2, a); merge_sort(n - n / 2, a + n / 2);

	c = merge_array(n / 2, a, n - n / 2, a + n / 2);

	for (i = 0; i < n; i++)a[i] = c[i];

	return;
}


// swap two doubles
void swap(double * a, double * b) {

	double temp;

	temp = *a; *a = *b; *b = temp;

}