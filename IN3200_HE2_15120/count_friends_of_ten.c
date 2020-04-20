#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
#include "string.h"

#include "count_friends_of_ten.h"

int count_friends_of_ten(int M, int N, int **v){
  int friends = 0;
  for(int i = 0; i < M-2; i ++){
    for(int j = 2; j < N; j++){
      if(v[i][j] + v[i+1][j-1] + v[i+2][j-2] == 10){ //backward diagonal
        friends ++;
      }
    }
    for(int j = 0; j < N-2; j++){
      if(v[i][j] + v[i+1][j+1] + v[i+2][j+2] == 10){ //forward diagonal
        friends ++;
      }
    }
    for(int j = 0; j < N; j++){
      if(v[i][j] + v[i+1][j] + v[i+2][j] == 10){ //vertical
        friends ++;
      }
    }
  }//end i loop to M-2

  for(int i=0; i < M; i++){
    for(int j = 2; j < N; j++){
    if(v[i][j]+v[i][j-1]+ v[i][j-2] == 10){//horizontal
      friends ++;
      }
    }
  }//end i loop to M
  return friends;
}
