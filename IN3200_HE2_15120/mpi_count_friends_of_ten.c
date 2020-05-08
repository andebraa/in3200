#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include "string.h"


int MPI_count_friends_of_ten(int M, int N, int** v){
  int friends = 0;
  int comm_sz;
  int my_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  printf("comm %d\n", comm_sz);

  int * rows = (int*)calloc(comm_sz+1, sizeof(int));
  if(my_rank==0){
    for(int i = 0; i < (comm_sz); i++){
      rows[i +1] = rows[i] + (M/comm_sz-1); //stores cumulative number of rows
    }
    //note! whenever using comm_sz, you must subtract 1 to get index
    rows[comm_sz] = M-1; //last element is given the rest
    //this might lead to load imbalance if rest is very large
    MPI_Bcast(rows, comm_sz+1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(N, 1, MPI_INT, 0, MPI_COMM_WORLD); //Sending size of rows, since all threads
    //will recive full rows

    //sending rows to other threads EXCEPT last thread as it does not want ghost rows
    for(int i = 1; i < comm_sz-1; i ++){//loop over threads except last thread
      for(int r = rows[i]+1; r < rows[i+1]+2; r ++){//loops over number of rows for each thread
        //in order to calculate vertical friends it needs two ghost rows
        MPI_Send(v[r], N, MPI_INT, i, 0, MPI_COMM_WORLD);
        // data, count, data type, destination, tag, communicator
        // i is the thread which data is sent to
      }
    }
    //the last thread is given the bottom rows, hence it can not be given
    //and ghost rows! comm_sz -1 is the last thread, who's index is comm_sz
    for(int r = rows[comm_sz-1]; r < rows[comm_sz]; r ++){
      MPI_send(v[r], N, MPI_INT, comm_sz-1, 0, MPI_COMM_WORLD);
    }


    CALCULATE RANK 0 FRIENDS HERE

  }else if(my_rank == (comm_sz-1)){ //last block does can not include ghost points
  int n;
  int * rows = (int*)calloc(comm_sz+2, sizeof(int));
  MPI_Bcast(rows, comm_sz+1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(N, 1, MPI_INT, 0, MPI_COMM_WORLD);
  //callocating memory for the rows this thread will recieve
  v = (int**)calloc(rows[comm_sz]-rows[comm_sz-1], sizeof(int*));
  for(int i = 0; i < M; i++){
    (v)[i] = (int*)calloc(N, sizeof(int));
  }

  }else{ //all blocks and ranks inbetween first and last
  int n;
  int * rows = (int*)calloc(comm_sz+2, sizeof(int));
  MPI_Bcast(rows, comm_sz+1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(N, 1, MPI_INT, 0, MPI_COMM_WORLD);
  }

//the middle threads are given space for two ghost rows.
  v = (int**)calloc( (rows[my_rank+1] -rows[my_rank]) +2, sizeof(int*)); //making 2D array
  for(int i = 0; i < M; i++){
    (v)[i] = (int*)calloc(N, sizeof(int));
    for(int j = 0; j < N; j++){
  }

  
  for(int i = 1; i < comm_sz-1; i ++){//loop over threads except last thread
    for(int r = rows[i]+1; r < rows[i+1]+2; r ++){//loops over number of rows for each thread
      //in order to calculate vertical friends it needs two ghost rows
      MPI_Send(v[r], N, MPI_INT, i, 0, MPI_COMM_WORLD);
      // data, count, data type, destination, tag, communicator
      // i is the thread which data is sent to
    }
  }

  return friends;
}
