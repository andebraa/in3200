#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
#include "string.h"

#include "count_friends_of_ten.h"

int main(){
  int M = 4;
  int N = 4;

  int** v = (int**)calloc(M, sizeof(int*)); //making 2D array
  for(int i = 0; i < M; i++){
    (v)[i] = (int*)calloc(N, sizeof(int));
    for(int j = 0; j < N; j++){
      v[i][j] = 1 + rand()%N; //note, [] derefrences the variable once
    }
  }
  int num_friends = count_friends_of_ten(M, N, v);


  printf("number of friends of ten: %d\n", num_friends);

  for(int i = 0; i < M; i++){
    free(v[i]);
  }
  free(v);
  return EXIT_SUCCESS;
}//end main
