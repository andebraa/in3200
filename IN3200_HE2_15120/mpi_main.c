#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include "omp.h"
#include "string.h"
#include "mpi_count_friends_of_ten.h"

int main (int argc, char **argv){
  int M=0, N=0, rank, num_triple_friends;
  int **v=NULL;
  time_t t;
  srand((unsigned) time(&t));
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank==0) {
    M = 9;
    N = 9;
    v = (int**)calloc(M, sizeof(int*)); //making 2D array
    for(int i = 0; i < M; i++){
      (v)[i] = (int*)calloc(N, sizeof(int));
      for(int j = 0; j < N; j++){
        v[i][j] = 1 + rand()%9; //note, [] derefrences the variable once
      }
    }

  } //end rank = 0

  num_triple_friends =MPI_count_friends_of_ten (M, N, v);

  printf("MPI rank <%d>: number of triple friends=%d\n", rank, num_triple_friends);


  if (rank==0){
    for(int i = 0; i < M; i++){
      free(v[i]);
    }
  free(v);
  }

  MPI_Finalize ();
  return 0;
}
