#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
#include <time.h>


int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){
  #if defined(_OPENMP)
  { //cml2 

    int mutual_link, tmp, row_count = 0; //number of elements on a given row
    #pragma omp parallel num_threads(4)
    {
      #pragma omp for reduction(+:mutual_link, num_involvements[:N])
      for(int i = 0; i < N; i++){//row number i is 'to'
        tmp = row_ptr[i];
        row_count = row_ptr[i+1] - row_ptr[i]; //number of elements in the given row
        for(int j = 0; j < row_count; j ++){
          num_involvements[col_idx[tmp+j]] += row_count -1;
          mutual_link += j;
        }
      }
    }//end pragma omp

    return mutual_link;
  }//END IFDEF
  #else
  {
    int mutual_links, tmp, row_count = 0; //number of elements on a given row
    for(int i = 0; i < N; i++){//row number i is to
      tmp = row_ptr[i];
      row_count = row_ptr[i+1] - row_ptr[i]; //number of elements in the given row
      //mutual_links += (row_count-1)*(row_count/2); //number og mutual links in the row

      for(int j = 0; j < row_count; j ++){
        num_involvements[col_idx[tmp+j]] += row_count -1;
        mutual_links += j;
      }

    }

    return mutual_links;
  }//end else
  #endif
}//end main
