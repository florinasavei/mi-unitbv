//
//  array.c
//  
//
//  Created by student on 28/02/2019.
//

#include <stdio.h>
#include<stdlib.h>
#include "mpi.h"

double array_Sum(int n, double *array);
int MPI_Array_sum(int n, double *array, double *finalSum, int root, MPI_Comm comm);

int main(int argc,char **argv){
    int rank,size;
    int n=1000000;
    double sum,overall_time;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    
    double *a = (double*)calloc(n,sizeof(double));
    if(rank==0)
    {
        for(int i=0;i<n;i++)
            a[i]=1.0;//a[i]=10.0*rand()/MAX_RAND;
    }
    
    double time=MPI_Wtime();
    MPI_Array_sum(n,a,&sum,0,MPI_COMM_WORLD);
    time=MPI_Wtime()-time;
    
    MPI_Reduce(&time,&overall_time,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
    
    if(rank==0)
        printf("Parallel sum finds the %lf in the time %lf \n",sum,overall_time);
    MPI_Finalize();
    
}

double array_Sum(int n, double *array){
    double sum=0;
    for (int i=0;i<n;i++)
        sum+=array[i];
    return sum;
}


int MPI_Array_sum(int n, double *array, double *finalSum, int root, MPI_Comm comm){
    int rank,size,rc;
    MPI_Comm_size(comm,&size);
    MPI_Comm_size(comm,&rank);
    double *localArray = (double *)calloc(n/size,sizeof(double));
    
    //scatter
    rc = MPI_Scatter(array,n/size,MPI_DOUBLE,localArray,n/size,MPI_DOUBLE,root,comm);
   
    
    //compute
    double sum=array_Sum(n/size,localArray);
    //reduce
    rc=MPI_Reduce(&sum,finalSum,1,MPI_DOUBLE,MPI_SUM,root,comm);
  
    return MPI_SUCCESS;
    
}
