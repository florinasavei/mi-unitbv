#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>

//MPI sort methods
int MPI_Direct_Sort(int n, double *a, int root, MPI_Comm comm);
//helper methods
double * merge_array(int n, double * a, int m, double * b);
void     merge_sort(int n, double * a);
void     swap(double * a, double * b);

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


	const double time1 = MPI_Wtime();
	MPI_Direct_Sort(nrElems, array, 0, MPI_COMM_WORLD);

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

int MPI_Direct_Sort(int n, double *a, int root, MPI_Comm comm)
{
	int rank, size;
	//find rank size
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);

	//allocate local_a
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
// function returns the merged array
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
	if (n <= 1) return;

	if (n == 2) {

		if (a[0] > a[1])swap(&a[0], &a[1]);
		return;
	}

	merge_sort(n / 2, a); merge_sort(n - n / 2, a + n / 2);

	double* c = merge_array(n / 2, a, n - n / 2, a + n / 2);

	for (int i = 0; i < n; i++)a[i] = c[i];
}


// swap two doubles
void swap(double * a, double * b) {
	const double temp = *a; *a = *b; *b = temp;
}