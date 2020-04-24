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
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank==0) {
    int M = 7;
    int N = 10;
    v = (int**)calloc(M, sizeof(int*)); //making 2D array
    for(int i = 0; i < M; i++){
      (v)[i] = (int*)calloc(N, sizeof(int));
      for(int j = 0; j < N; j++){
        v[i][j] = 1 + rand()%N; //note, [] derefrences the variable once
      }
    }
    /*
    for(int i = 0; i < M; i++){
      for(int j = 0; j < N; j++){
        printf("  %d  ", v[i][j]);
      }
      printf("\n");
    }
    printf("end main loop \n");
    */
  } //end rank = 0
  num_triple_friends = MPI_count_friends_of_ten (M, N, v);
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
