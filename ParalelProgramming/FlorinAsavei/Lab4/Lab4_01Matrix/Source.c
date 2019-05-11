
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

// utility functions
int ** alloc_matrix(int n, int m);
void init_matrix(int n, int m, int ** a);
void print_matrix(int n, int m, int ** a);

// matrix operations
int ** prod_matrix(int n, int l, int m, int ** a, int ** b);
int ** trans_matrix(int n, int m, int ** a);

// MPI functions
int MPI_Prod_matrix(int n, int ** a, int ** b, int ** c, int root, MPI_Comm comm);

int main(int argc, char ** argv) {
	int size, rank, tag = 1, i, j, n = 20, **a, **b, **c, **a1, **c1;
	double time;

	MPI_Status stat;
	MPI_Datatype rowtype;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Type_contiguous(n, MPI_INT, &rowtype);
	MPI_Type_commit(&rowtype);

	a = alloc_matrix(n, n);
	b = alloc_matrix(n, n);
	c = alloc_matrix(n, n);

	if (rank == 0) {

		// initialise the matrices

		init_matrix(n, n, a);
		init_matrix(n, n, b);

	}

	time = MPI_Wtime();

	MPI_Prod_matrix(n, a, b, c, 0, MPI_COMM_WORLD);

	time = MPI_Wtime() - time;

	printf("\nProcessor %d worked for %lf\n\n", rank, time);

	if (rank == 0) {

		// initialise the matrices

		printf("Matrix a:\n\n"); print_matrix(n, n, a);
		printf("\nMatrix b:\n\n"); print_matrix(n, n, b);
		printf("\nMatrix c:\n\n"); print_matrix(n, n, c);


	}


	MPI_Type_free(&rowtype);
	MPI_Finalize();
}



int MPI_Prod_matrix(int n, int ** a, int ** b, int ** c, int root, MPI_Comm comm)
{
	int rank, size;
	// get rank and size of comm
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);

	// alocate space for local_a and local_c
	int **local_a = alloc_matrix(n / size, n);
	int **local_c = alloc_matrix(n / size, n);

	// scatter a to local_a and bcast_b
	MPI_Scatter(a[0], n*n/size, MPI_INT, local_a[0], n*n/size, MPI_INT, root, comm);
	MPI_Bcast(b[0], n*n, MPI_INT, root, comm);

	// calculate local_c = local_a * b
	local_c = prod_matrix(n / size, n, n, local_a, b);

	// gather local_c
	MPI_Gather(local_c[0], n*n / size, MPI_INT, c[0], n*n / size, MPI_INT, root, comm);

	return MPI_SUCCESS;
}


/*

The function alloc_matrix is to allocate dynamically a matrix of integers with
 n rows and m columns.

The function arguments are;

	n - number of rows
	m - number of columns

The function returns the double pointer representing the matrix.



*/

int ** alloc_matrix(int n, int m) {

	int i, j, **a, *aa;

	aa = (int *)calloc(n*m, sizeof(int));
	a = (int **)calloc(n, sizeof(int*));

	for (i = 0; i < n; i++)a[i] = aa + i * m;

	for (i = 0; i < n; i++)for (j = 0; j < m; j++)a[i][j] = 0;

	return a;
}


/*

The function init_matrix is to initialize the matrix a with random integers.

The function arguments are:

	n - number of rows
	m - number of columns
	a - the matrix


*/



void init_matrix(int n, int m, int ** a) {

	int i, j;

	for (i = 0; i < n; i++)for (j = 0; j < m; j++)a[i][j] = rand() % 10;


}


/*

The function print_matrix is to display the matrix a.

The function arguments are:

	n - number of rows
	m - number of columns
	a - the matrix


*/



void print_matrix(int n, int m, int ** a) {

	int i, j;

	printf("\n");

	for (i = 0; i < n; i++) {

		for (j = 0; j < m; j++)printf("%d ", a[i][j]);

		printf("\n");

	}


}


/*

The function prod_matrix is to multiply the matrices a and b.

The function arguments are;

	n - number of rows of a
	l - number of columns of a // the matrix b must have l rows
	m - number of columns of b

	a - the first matrix
	b - the second matrix

The function returns the double pointer representing the product matrix.



*/


int ** prod_matrix(int n, int l, int m, int ** a, int ** b) {

	int i, j, k, ** c;

	c = alloc_matrix(n, m);

	for (i = 0; i < n; i++)for (j = 0; j < m; j++) {

		c[i][j] = 0;

		for (k = 0; k < l; k++) {
			c[i][j] = c[i][j] + a[i][k] * b[k][j];
		}

	}

	return c;

}


int ** trans_matrix(int n, int m, int ** a) {

	int i, j;
	int ** b;

	b = alloc_matrix(m, n);

	for (j = 0; j < m; j++)for (i = 0; i < n; i++) {

		b[j][i] = a[i][j];

	}

	return b;

}