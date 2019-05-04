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
int isSorted(int n, double* aa, MPI_Comm comm);
int compare(const void* a, const void* b);
int MPI_Direct_sort(int n, double* a, int root, MPI_Comm comm);
int MPI_Ranking_sort(int n, double* a, int root, MPI_Comm comm);
int MPI_Bucket_sort(int n, double m, double* a, int root, MPI_Comm comm);
int MPI_OddEven_sort(int n, double* a, int root, MPI_Comm comm);
void exchange(int n, double* aa, int sender, int receiver, MPI_Comm comm);
//utility methods
double* merge_array(int n, double* a, int m, double* b);
void     merge_sort(int n, double* a);
void     swap(double* a, double* b);

int main(int argc, char* argv[])
{

	int rank, size;

	int n = 100000, i, j, k, x, q, l, shell, pair, *nr;
	double m = 200.0;
	double* scattered_array, *array = NULL;

	// Init + rank + size
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	array = (double*)calloc(n, sizeof(double));

	if (rank == 0)
	{

		//initialise the array with random values, then scatter to all processors
		srand(((unsigned)time(NULL) + rank));

		for (i = 0; i < n; i++)
		{
			array[i] = ((double)rand() / RAND_MAX) * m;
		}

	}

	if (rank == 0)
	{
		//for (int i = 0; i < n; i++)printf("%lf ", array[i]);
	}


	double time1 = MPI_Wtime();
	//MPI_Direct_sort(n, array, 0, MPI_COMM_WORLD);
	//MPI_Ranking_sort(n, array, 0, MPI_COMM_WORLD);
	//MPI_Bucket_sort(n,m, array, 0, MPI_COMM_WORLD);
	MPI_OddEven_sort(n, array, 0, MPI_COMM_WORLD);

	printf("Processor %d worked for %lf\n", rank, MPI_Wtime() - time1);

	if (rank == 0)
	{
		//for (int i = 0; i < n; i++)printf("%lf ", array[i]);
	}

	MPI_Finalize();

}


int MPI_Direct_sort(int n, double* a, int root, MPI_Comm comm)
{
	int rank, size;
	//find rank size
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);

	//alocate local_a

	double* local_a = (double*)calloc(n / size, sizeof(double));
	//scatter array
	MPI_Scatter(a, n / size, MPI_DOUBLE, local_a, n / size, MPI_DOUBLE, root, comm);

	//sort scattered arrays
	merge_sort(n / size, local_a);

	//gather
	MPI_Gather(local_a, n / size, MPI_DOUBLE, a, n / size, MPI_DOUBLE, root, comm);

	//processor 0 merges size-1 chunks

	if (rank == 0) {
		for (int i = 1; i < size; i++) {
			double* tmp = merge_array(i * n / size, a, n / size, a + i * n / size);
			for (int j = 0; j < (i + 1) * n / size; j++)a[j] = tmp[j];
		}
	}
	return MPI_SUCCESS;
}

// function to merge the array a with n elements with the array b with m elements
// function returns the nerged array

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

// function to merge sort the array a with n elements

void merge_sort(int n, double* a) {

	double* c;
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
void swap(double* a, double* b) {

	double temp;

	temp = *a; *a = *b; *b = temp;

}
int MPI_Ranking_sort(int n, double* a, int root, MPI_Comm comm)
{
	int rank, size;
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);

	int* ranking = (int*)calloc(n / size, sizeof(int));
	int* overallRanking = (int*)calloc(n, sizeof(int));

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
		double* tmp = (double*)calloc(n, sizeof(double));
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

int MPI_Bucket_sort(int n, double m, double* a, int root, MPI_Comm comm)
{
	int size, rank, count = 0;
	MPI_Comm_rank(comm, &size);
	MPI_Comm_size(comm, &rank);
	int *counters = (int*)calloc(size, sizeof(int));
	int *displ = (int*)calloc(size, sizeof(int));

	double* bucket = (double*)calloc(n, sizeof(double));
	MPI_Bcast(&a[0], n, MPI_DOUBLE, root, comm);

	for (int i = 0; i < n; i++)
	{
		if (rank * m / size <= a[i] && a[i] < (rank + 1) * m / size)
			bucket[count++] = a[i];
	}
	qsort(bucket, count, sizeof(double), compare);

	MPI_Gather(&count, 1, MPI_INT, counters, 1, MPI_INT, root, comm);

	//create displ array
	displ[0] = 0;
	for (int i = 0; i < size - 1; i++)
	{
		displ[i + 1] = displ[i] + counters[i];
	}

	MPI_Gatherv(bucket, count, MPI_DOUBLE, a, counters, displ, MPI_DOUBLE, root, comm);

	return MPI_SUCCESS;
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
	int rank, size, ok = 1, totalOk;
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

