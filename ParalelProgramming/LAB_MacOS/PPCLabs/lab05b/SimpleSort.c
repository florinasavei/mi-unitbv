#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int MPI_Sort_ranking(int n, double * a, double max, int root, MPI_Comm comm);

int main (int argc, char *argv[])
{

	int rank, size;

	int n = 12000, q, l, i, j, k, x, *nr;
	double m = 10.0;
	double *a, *b;

	MPI_Status status;

	MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int* ranking =(int*)calloc(n/size, sizeof(int));
    int* allRanking = (int*)calloc(, sizeof(int));
    
    MPI_Bcast(a, n, MPI_DOUBLE, root, comm);

	a = (double *) calloc(n,sizeof(double));
	b = (double *) calloc(n,sizeof(double));

	if( rank == 0 )
	{

	   //initialise the array with random values, then scatter to all processors
	   srand( ((unsigned)time(NULL)+rank) );

	   for( i = 0; i < n; i++ )
	   {
	      a[i]=((double)rand()/RAND_MAX)*m;
	      printf( "Initial: %f\n", a[i] );
	   }

	}

	MPI_Sort_ranking(n, a, m, 0, MPI_COMM_WORLD);

	if( rank == 0 )
	{
	   for( i = 0; i < n; i++ )
	   {
	      printf( "Output : %f\n", a[i] );
	   }
	}
	MPI_Finalize();

}

int MPI_Sort_ranking(int n, double * a, double max, int root, MPI_Comm comm)
{
    // find rank and size
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    
    // allocate the extra memory / arrays needed
    int* ranking =(int*)calloc(n/size, sizeof(int));
    int* allRanking = (int*)calloc(, sizeof(int));
    double * b=(double*)calloc(n, sizeof(double));
	
	// Brodcast the array to the processor
	MPI_Bcast(a, n, MPI_DOUBLE, root, comm);
    
    // P rank generates an array ranking with ranking[i] is the rank of a[i+rank*n/size] in the array
    for(int i-0; i<n/size; i++){
        ranking[i]=0;
        for(int j=0; j<n; j++){
            if(a[i+rank*n/size]>a[j]){
                ranking[i]++;
            }
        }
    }
    
	// Gather the array ranking to finalRanking
    MPI_Gather(ranking, n/size, MPI_INT, allRanking, n/size, MPI_INT, root, comm);
    
	// if processor 0 then restore the order in the array b and move b back to a
    if(rank==0){
        //restore order
        for(int i=0; i<n; i++){
            b[allRanking[i]]=a[i];
        }
        for(int i=0; i<n; i++){
            a[i]=b[i];
        }
    }
	
}
