//
//  rps.c
//  
//
//  Created by student on 30/03/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "mpi.h"

//________function declaration

int game(int move1, int move2);

//--------main function

int main(int argc, char** argv){
    
    //intitializeaza contextul paralele
    MPI_Init(&argc, &argv);
    
    //gaseste rank, size
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    //data pt P rank
    unsigned int iseed = (unsigned int)time(NULL);
    srand(iseed*rank);       // seed the generator with a different seed.
    int move = rand()%3;
    
    //ping pong move to otherMove
    int tag1=1, tag2=2, otherMove;
    int winner;
    MPI_Status status;
    
    if(rank == 0){
        MPI_Send(&move, 1, MPI_INT, 1, tag1, MPI_COMM_WORLD);
        MPI_Recv(&otherMove, 1, MPI_INT, 1, tag2, MPI_COMM_WORLD, &status);
        
        winner = game(move, otherMove);
    }else if(rank == 1){
        MPI_Recv(&otherMove, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD, &status);
        MPI_Send(&move, 1, MPI_INT, 0, tag2, MPI_COMM_WORLD);
        
        winner = game(otherMove, move);
    }
    
    printf("Processor %d finds Game won by %d\n", rank, winner);
    
    return 1;
    
    
}

//--------function definitions

int game(int move0, int move1){
    char *moves = "rps";
    char m0 = moves[move0], m1 = moves[move1];
    
    if(m0 == m1) return -1;
    else if((m0 == 'p' && m1 == 'r') || (m0 == 'r' && m1 == 's')|| (m0 == 's' && m1 == 'p')) return 0;
    else return 1;
    
}
