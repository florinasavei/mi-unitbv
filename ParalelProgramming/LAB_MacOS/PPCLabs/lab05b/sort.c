/**
 * MPI Program that performs simple sorting
 *
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"



double * merge_array(int n, double * a, int m, double * b);
void     merge_sort(int n, double * a);
void     swap (double * a, double * b);
int MPI_Direct_sort(int n, double *a, int root, MPI_Comm comm);
int MPI_Ranking_sort(int n, double * a, double max, int root, MPI_Comm comm);

int main (int argc, char *argv[])
{

	int rank, size;

	int n = 1200000, i, j, k, x, q, l, shell, pair, *nr;
	double m = 10.0;
	double * scattered_array, * array = (double *) calloc( n, sizeof(double) );

	// Init + rank + size
	MPI_Init(&argc, &argv);
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   	MPI_Comm_size(MPI_COMM_WORLD, &size);


	if( rank == 0 )
	{

	   //initialise the array with random values, then scatter to all processors
       
	   srand( ((unsigned)time(NULL)+rank) );

	   for( i = 0; i < n; i++ )
	   {
	      array[i]=((double)rand()/RAND_MAX)*m;
	   }

	}

    double time1=MPI_Wtime();
    MPI_Ranking_sort(n, array, m, 0, MPI_COMM_WORLD);
    double time2=MPI_Wtime();

    printf("Processor %d works for %f\n", rank, time2-time1);
    
	if( rank == 0 )
	{
        //for(int i=0; i<n; i++){
          //  printf("%lf\n", array[i]);
        //}
	}

	MPI_Finalize();

}

// function to merge the array a with n elements with the array b with m elements
// function returns the nerged array

double * merge_array(int n, double * a, int m, double * b){

   int i,j,k;
   double * c = (double *) calloc(n+m, sizeof(double));

   for(i=j=k=0;(i<n)&&(j<m);)

      if(a[i]<=b[j])c[k++]=a[i++];
      else c[k++]=b[j++];

   if(i==n)for(;j<m;)c[k++]=b[j++];
   else for(;i<n;)c[k++]=a[i++];

return c;
}

// function to merge sort the array a with n elements

void merge_sort(int n, double * a){

   double * c;
   int i;

   if (n<=1) return;

   if(n==2) {

      if(a[0]>a[1])swap(&a[0],&a[1]);
      return;
   }



   merge_sort(n/2,a);merge_sort(n-n/2,a+n/2);

   c=merge_array(n/2,a,n-n/2,a+n/2);

   for(i=0;i<n;i++)a[i]=c[i];

return;
}


// swap two doubles
void swap (double * a, double * b){

   double temp;

   temp=*a;*a=*b;*b=temp;

}

int MPI_Direct_sort(int n, double *a, int root, MPI_Comm comm){
    
    // find rank and size
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    
    //allocate local_a
    double * local_a=(double *)calloc(n, sizeof(double));
    
    //scatter a to local_a
    MPI_Scatter(a, n/size, MPI_DOUBLE, local_a, n/size, MPI_DOUBLE, root, comm);
    
    //sort local_a
    merge_sort(n/size, local_a);
    
    //gather local_a to a
    MPI_Gather(local_a, n/size, MPI_DOUBLE, a, n/size, MPI_DOUBLE, root, comm);
    
    //if 0 then merge size-1 chunks
    if(rank == 0){
        for(int i=0; i<size; i++){
            double * tmp = merge_array(i*n/size, a, n/size, a+i*n/size);
            for(int j=0; j<(i+1)*n/size; j++){
                a[j]=tmp[j];
            }
        }
    }
    
    return MPI_SUCCESS;
}

int MPI_Ranking_sort(int n, double * a, double max, int root, MPI_Comm comm)
{
    // find rank and size
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    
    // allocate the extra memory / arrays needed
    int* ranking =(int*)calloc(n/size, sizeof(int));
    int* allRanking = (int*)calloc(n, sizeof(int));
    double * b=(double*)calloc(n, sizeof(double));
    
    // Brodcast the array to the processor
    MPI_Bcast(a, n, MPI_DOUBLE, root, comm);
    
    // P rank generates an array ranking with ranking[i] is the rank of a[i+rank*n/size] in the array
    for(int i=0; i<n/size; i++){
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
    
    return MPI_SUCCESS;
    
}
