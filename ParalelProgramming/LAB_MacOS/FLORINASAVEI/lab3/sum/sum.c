/***************************************************************
 MPI program to compute an array operation
 ****************************************************************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

//declare functions
long sum_array(int n, int * a);
int MPI_Sum_array(int n, int * a, long * sum, int root, MPI_Comm comm);

int max_array(int n, int *a);
int MPI_Max_array(int n, int *a, int *max, int root, MPI_Comm comm);

//main function
int main(int argc, char * argv []) {
    int * array;
    int n = 1000;
    int n1;
    int size, rank;
    // declare and initialise the variables for sum, prod, max and min
    long sum = 0;
    int max=-10000;
    // Init + rank + size
    MPI_Init (&argc,&argv);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    // populate the array a if processor 0
    // serial code
    if (rank == 0) {
        // Processor 0 is the only one to know array
        array = (int *)calloc(n, sizeof(int));
        for(int i=0;i<n;i++)
            array[i]=1; // you can initialise with a random number
    }
    double time1=MPI_Wtime();
    //MPI_Sum_array(n,array,&sum,0,MPI_COMM_WORLD);
    MPI_Max_array(n,array,&max,0,MPI_COMM_WORLD);
    double time2=MPI_Wtime();
    printf("Processor %d works for %lf\n", rank, time2-time1);
    if(rank==0){
        // Write final_sum, final_prod, final_max and final_min
        //printf("the final sum is %ld\n", sum);
        printf("the max  is %d", max);
    }
    MPI_Finalize ();
}

//----- function declarations

long sum_array(int n, int * a){
    long sum =0;
    for(int i =0; i <n;i++){
        sum +=a[i];
    }
    return sum;
}

int max_array(int n, int * a){
    int max = a[0];
    
    for(int i=0; i<n; i++){
        if(a[i]>max) max=a[i];
    }
    
    return max;
}

int MPI_Sum_array(int n, int * a, long * sum, int root, MPI_Comm comm){
    //find rank and size
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    
    //allocate local_a
    int * local_a = (int *)calloc(n/size,sizeof(int));
    MPI_Scatter(&a[0], n/size, MPI_INT, &local_a[0],n/size,MPI_INT,root,comm);
    long local_sum = sum_array(n/size,local_a);
    MPI_Reduce(&local_sum,sum,1,MPI_LONG, MPI_SUM,root, comm);
    //scatter
    //compute sum of local_a
    //reduce local_sum by MPI_SUM
    
    return MPI_SUCCESS;
}

int MPI_Max_array(int n, int * a, int * max, int root, MPI_Comm comm){
    
    //find rank and size
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    
    //allocate local_a
    int * local_a = (int *)calloc(n/size,sizeof(int));
    
    //scatter
    MPI_Scatter(&a[0], n/size, MPI_INT, &local_a[0],n/size,MPI_INT,root,comm);
    
    //compute sum of local_a
    int local_max = max_array(n/size,local_a);
    
    MPI_Reduce(&local_max,max,1,MPI_LONG, MPI_SUM,root, comm);
    //reduce local_sum by MPI_SUM
    
    return MPI_SUCCESS;
    
}
