#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include "omp.h"
#include "string.h"


int MPI_count_friends_of_ten(int M, int N, int ** v){
  printf("inside count friends \n");
  int friends = 0;
  int comm_sz;
  int my_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  /*
  if(M%comm_sz != 0){

  }
  for(int i = 0; i < comm_sz; i++){

  }
  */
//  if(my_rank==1){
    for(int i = 0; i < M; i++){
      for(int j = 0; j < N; j++){
        printf("  %d  ", v[i][j]);
      }
      printf("\n");
    }
    printf("end friend loop \n");
//  }else if(my_rank == comm_sz){ //last block does can not include ghost points

  //}else{ //all blocks and ranks inbetween first and last

  //}

  return friends;
}
