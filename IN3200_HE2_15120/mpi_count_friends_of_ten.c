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
  int * rows = (int*)calloc(comm_sz+1, sizeof(int));

  if(my_rank==0){

    int friends_local = 0;
    for(int i = 0; i < (comm_sz); i++){
      rows[i +1] = rows[i] + ((M/comm_sz)-1); //stores cumulative number of rows
    }
    //note! whenever using comm_sz, you must subtract 1 to get index
    rows[comm_sz] = M-1; //last element is given the rest
    //this might lead to load imbalance if rest is very large
    MPI_Bcast(rows, comm_sz+1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD); //Sending size of rows, since all threads
    //will recive full rows

    //sending rows to other threads EXCEPT last thread as it does not want ghost rows
    for(int i = 1; i < comm_sz-1; i ++){//loop over threads except last thread
      for(int r = rows[i]+1; r < rows[i+1]+2; r ++){//loops over number of rows for each thread
        //in order to calculate vertical friends it needs two ghost rows
        MPI_Send(v[r], N, MPI_INT, i, i, MPI_COMM_WORLD); //trying to use tag = thread
        // data, count, data type, destination, tag, communicator
        // i is the thread which data is sent to
      }
    }
    //the last thread is given the bottom rows, hence it can not be given
    //and ghost rows! comm_sz -1 is the last thread, who's index is comm_sz
    for(int r = rows[comm_sz-1]+1; r <= rows[comm_sz]; r ++){
      MPI_Send(v[r], N, MPI_INT, comm_sz-1, comm_sz-1, MPI_COMM_WORLD);
    }

    //calculating rank 0 friends from row 0 to row rows[1]+2
    for(int i = 0; i < rows[1]; i++){
      for(int j = 2; j < N; j++){
        if(v[i][j] + v[i+1][j-1] + v[i+2][j-2] == 10){ //backward diagonal
          friends_local ++;
        }
      }
      for(int j = 0; j < N-2; j++){
        if(v[i][j] + v[i+1][j+1] + v[i+2][j+2] == 10){ //forward diagonal
          friends_local ++;
        }
        if(v[i][j]+v[i][j+1]+ v[i][j+2] == 10){//horizontal
          friends_local ++;
        }
      }
      for(int j = 0; j < N; j++){
        if(v[i][j] + v[i+1][j] + v[i+2][j] == 10){ //vertical
          friends_local ++;
        }
      }
    }//end i loop rows[1\\\\\\    MPI_Allreduce(&friends_local, &friends, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    free(rows);

    //return or share the number of friends of ten
    MPI_Allreduce(&friends_local, &friends, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

  }else if(my_rank == (comm_sz-1)){ //last block does can not include ghost points

  int friends_local=0;
  int N;
  int * rows = (int*)calloc(comm_sz+2, sizeof(int));
  MPI_Bcast(rows, comm_sz+1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
  //callocating memory for the rows this thread will recieve
  int **v_f = (int**)calloc(rows[comm_sz]-rows[comm_sz-1], sizeof(int*));
  for(int i = 0; i < rows[comm_sz]-rows[comm_sz-1]; i++){
    (v_f)[i] = (int*)calloc(N, sizeof(int));
  }

  for(int r = 0; r < rows[comm_sz] -rows[comm_sz-1]; r++){
    MPI_Recv(v_f[r], N, MPI_INT, 0, comm_sz-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  //calculating last thread friends from rows[comm_sz-1]+1 to rows[comm_sz]-2
  for(int i = 0; i < rows[comm_sz] -rows[comm_sz-1]-2; i++){ //last thread bottoms out at rows[comm_sz]-2
    for(int j = 2; j < N; j++){
      if(v_f[i][j] + v_f[i+1][j-1] + v_f[i+2][j-2] == 10){ //backward diagonal
        friends_local ++;
      }
    }
    for(int j = 0; j < N-2; j++){
      if(v_f[i][j] + v_f[i+1][j+1] + v_f[i+2][j+2] == 10){ //forward diagonal
        friends_local ++;
      }
    }
    for(int j = 0; j < N; j++){
      if(v_f[i][j] + v_f[i+1][j] + v_f[i+2][j] == 10){ //vertical
        friends_local ++;
      }
    }
  }//end i loop rows[1]
  for(int i = 0; i < rows[comm_sz] -rows[comm_sz-1]; i++){//want to compute horizontal all the way down
    for(int j = 0; j < N; j++){
      if(v_f[i][j]+v_f[i][j+1]+ v_f[i][j+2] == 10){//horizontal
        friends_local ++;
      }
    }
  }

  //return or share the number of friends of ten
  MPI_Allreduce(&friends_local, &friends, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);


  for(int i = 0; i <rows[comm_sz]-rows[comm_sz-1]; i++){ //free the slaves
    free(v_f[i]);
  }
  free(v_f);
  free(rows);

  }else{ //all blocks and ranks inbetween first and last
  int friends_local=0;
  int N;
  int * rows = (int*)calloc(comm_sz+2, sizeof(int));
  MPI_Bcast(rows, comm_sz+1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

  //the middle threads are given space for two ghost rows.
    int **v_m = (int**)calloc( (rows[my_rank+1] -rows[my_rank]) +2, sizeof(int*)); //making 2D array
    for(int i = 0; i < (rows[my_rank+1] -rows[my_rank]) +2; i++){
      (v_m)[i] = (int*)calloc(N, sizeof(int));
    }

    for(int i = 1; i < comm_sz-1; i ++){//loop over threads except last thread
      for(int r = 0; r < (rows[my_rank+1] -rows[my_rank]) +2; r ++){//loops over number of rows for each thread
        //in order to calculate vertical friends it needs two ghost rows
        MPI_Recv(v_m[r], N, MPI_INT, i, my_rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // data, count, data type, destination, tag, communicator
        // i is the thread which data is sent to
      }
    }

    //calculating mid rank friends from row rows[my_rank] to row rows[my_rank+1]+2
    for(int i = 0; i < (rows[my_rank+1] -rows[my_rank]); i++){ //last thread bottoms out at rows[comm_sz]-2
      for(int j = 2; j < N; j++){
        if(v_m[i][j] + v_m[i+1][j-1] + v_m[i+2][j-2] == 10){ //backward diagonal
          friends_local ++;
        }
      }
      for(int j = 0; j < N-2; j++){
        if(v_m[i][j] + v_m[i+1][j+1] + v_m[i+2][j+2] == 10){ //forward diagonal
          friends_local ++;
        }
        if(v_m[i][j]+v_m[i][j+1]+ v_m[i][j+2] == 10){//horizontal
          friends_local ++;
        }
      }
      for(int j = 0; j < N; j++){
        if(v_m[i][j] + v_m[i+1][j] + v_m[i+2][j] == 10){ //vertical
          friends_local ++;
        }
      }
    }//end i loop rows[1]

    //return or share the number of friends of ten
    MPI_Allreduce(&friends_local, &friends, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    for(int i = 0; i <N; i++){ //free the slaves
      free(v_m[i]);
    }
    free(v_m);
    free(rows);

  }//end middle rows



  return friends;
}
