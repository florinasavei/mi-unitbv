#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>

//MPI sort methods
int MPI_OddEven_sort(int n, double* a, int root, MPI_Comm comm);
//utility methods
int compare(const void* a, const void* b);
void exchange(int n, double* aa, int sender, int receiver, MPI_Comm comm);
int isSorted(int n, double* aa, MPI_Comm comm);
double* merge_array(int n, double* a, int m, double* b);

int main(int argc, char* argv[])
{

	int rank, size;

	const int nrElems = 1000000;
	const double m = 200.0;

	// Init + rank + size
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	double* array = (double*)calloc(nrElems, sizeof(double));

	if (rank == 0)
	{

		//initialise the array with random values, then scatter to all processors
		srand(((unsigned)time(NULL) + rank));

		for (int i = 0; i < nrElems; i++)
		{
			array[i] = ((double)rand() / RAND_MAX) * m;
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

	MPI_OddEven_sort(nrElems, array, 0, MPI_COMM_WORLD);

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


int MPI_OddEven_sort(int n, double* a, int root, MPI_Comm comm)
{
	int rank, size, ok, totalOk;
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);

	double* aa = (double*)calloc(n / size, sizeof(double));

	MPI_Scatter(&a[0], n / size, MPI_DOUBLE, aa, n / size, MPI_DOUBLE, root, comm);
	qsort(aa, n / size, sizeof(double), compare);

	for (int i = 0; i < size; i++)
	{
		ok = isSorted(n / size, aa, comm);

		MPI_Allreduce(&ok, &totalOk, 1, MPI_INT, MPI_MIN, comm);

		if (totalOk == 1)
			break;

		if ((i + rank) % 2 == 0)
		{
			if (rank < size - 1)
				exchange(n / size, aa, rank, rank + 1, comm);
		}
		else
		{
			if (rank > 0)
				exchange(n / size, aa, rank - 1, rank, comm);

		}
		MPI_Barrier(comm);
	}

	MPI_Gather(aa, n / size, MPI_DOUBLE, a, n / size, MPI_DOUBLE, root, comm);

	return MPI_SUCCESS;

}

// function to merge the array a with n elements with the array b with m elements
// function returns the merged array
double* merge_array(int n, double* a, int m, double* b) {

	int i, j, k;
	double* c = (double*)calloc(n + m, sizeof(double));

	for (i = j = k = 0; (i < n) && (j < m);)

		if (a[i] <= b[j])c[k++] = a[i++];
		else c[k++] = b[j++];

	if (i == n)for (; j < m;)c[k++] = b[j++];
	else for (; i < n;)c[k++] = a[i++];

	return c;
}

int compare(const void* a, const void* b)
{
	if (*(double*)a > * (double*)b) {
		return 1;
	}
	else if (*(double*)a < *(double*)b)
	{
		return -1;
	}
	return 0;
}

void exchange(int n, double* aa, int sender, int receiver, MPI_Comm comm)
{
	int rank;
	MPI_Comm_rank(comm, &rank);
	MPI_Status status;

	double* b = (double*)calloc(n, sizeof(double));
	double* c;

	if (rank == sender)
	{
		MPI_Send(aa, n, MPI_DOUBLE, receiver, 1, comm);
		MPI_Recv(b, n, MPI_DOUBLE, receiver, 2, comm, &status);

		c = merge_array(n, aa, n, b);

		for (int i = 0; i < n; i++)
			aa[i] = c[i];
	}
	else
	{

		MPI_Recv(b, n, MPI_DOUBLE, sender, 1, comm, &status);
		MPI_Send(aa, n, MPI_DOUBLE, sender, 2, comm);

		c = merge_array(n, aa, n, b);

		for (int i = 0; i < n; i++)
			aa[i] = c[i + n];
	}
}
int isSorted(int n, double *aa, MPI_Comm comm)
{
	int rank, size, ok = 1;
	double temp;
	MPI_Status status;
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);

	if (rank < size - 1)
	{
		MPI_Send(&aa[n - 1], 1, MPI_DOUBLE, rank + 1, rank, comm);
	}
	if (rank > 0) {

		MPI_Recv(&temp, 1, MPI_DOUBLE, rank - 1, rank - 1, comm, &status);

		if (temp > aa[0])
		{
			ok = 0;
		}
	}

	return ok;
}

