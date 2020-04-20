#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
#include <time.h>
//note, count mutual links assumes read_graph_from_file has been called earlier

int count_mutual_links1(int N, char **table2D, int *num_involments){
  #if defined(_OPENMP)
    {
    int mutual_link = 0;
    #pragma omp parallel num_threads(4)
    {


      int myID=omp_get_thread_num ();
      int Nthrds = omp_get_num_threads();
      #pragma omp for reduction(+:mutual_link,num_involments[:N])
      for(int i = 0; i < N; i ++){ //collumn
        for(int j = 0; j < N; j++){ //row
          if(table2D[i][j] == 1){
            for(int k = j+1; k < N; k++){ //runs forom given index till the end
              //if(table2D[i][k] ==1){
                mutual_link += table2D[i][k];
                num_involments[j] += table2D[i][k];
                num_involments[k] += table2D[i][k];
                //printf("%d \n", num_involments[j]);
                // 0 0 1 0 1 1 0 1 = 6 involments
              //}
            }
          }
        }
      }
    }//end pragma omp paralell
    return mutual_link;
  }//end ifdef
  #else
    {


    int mutual_link = 0;
    for(int i = 0; i < N; i ++){ //collumn
      for(int j = 0; j < N; j++){ //row
        if(table2D[i][j] == 1){
          for(int k = j+1; k < N; k++){ //runs forom given index till the end
            mutual_link += table2D[i][k];
            num_involments[j] += table2D[i][k];
            num_involments[k] += table2D[i][k];
          }
        }
      }

    }
    return mutual_link;
  }//end #else
  #endif
}//end cm_links1
