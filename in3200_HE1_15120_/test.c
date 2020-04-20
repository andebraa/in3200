#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
#include "string.h"
#include <time.h>

#include "read_graph_from_file1.h"
#include "read_graph_from_file2.h"
#include "count_mutual_links1.h"
#include "count_mutual_links2.h"
#include "top_n_webpages.h"
#include "test.h"

int test(int argc, char **argv){
  printf("beginning test\n");

	int N, *num_involments; //N: nodes, N_links: edges
  if (argc != 2) {
    printf("Usage: %s <data file>\n", argv[0]);
    return EXIT_FAILURE;
  }
  char *filename = argv[1];
	char **table2D;

  //READ GRAPH FROM FILE 1 AND COUNT MUTUAL LINKS 1


  double start_rgff1, end_rgff1, start_rgff2, end_rgff2;
  double time_rgff1, time_rgff2;

  start_rgff1 = clock();
	read_graph_from_file1(filename, &N, &table2D);
  end_rgff1 = clock();

  time_rgff1 = (double)(end_rgff1 - start_rgff1)/CLOCKS_PER_SEC;
  printf("time: %f\n", time_rgff1);

	num_involments = calloc(N, sizeof(int)); //number of outbound links
	if (num_involments == NULL)  {
		perror("couldn't calloc");
		exit(-1);

	}


  double start_cml1, end_cml1;
	double time_cml1= 0;
  #if defined(_OPENMP)
    {

      start_cml1 = omp_get_wtime();
    	int cm_links1 = count_mutual_links1(N, table2D, num_involments);
      end_cml1 = omp_get_wtime();
      time_cml1 = end_cml1 - start_cml1;


    }
    #else
    {
      start_cml1 = clock();
      int cm_links1 = count_mutual_links1(N, table2D, num_involments);
      end_cml1 = clock();
      time_cml1 = (double)(end_cml1 - start_cml1)/CLOCKS_PER_SEC;

    }
  #endif



	for (int i = 0; i < N; i++) {
		free(table2D[i]);
	}
	free(table2D);
	free(num_involments);



  //READ GRAPH FROM FILE 2 AND COUNT MUTUAL LINKS 2


 	int *row_ptr, *col_idx, N_links, mutual_links;
  double time_cml2 = 0;
 	read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);


 	num_involments = calloc(N, sizeof(int)); //number of outbound links
 	if (num_involments == NULL)  {
 		perror("couldn't calloc");
 		exit(-1);

 	}

  double start_cml2, end_cml2;
  #if defined(_OPENMP)
  {

    start_cml2 = omp_get_wtime();
 	  mutual_links = count_mutual_links2(N,N_links, row_ptr, col_idx, num_involments);
    end_cml2 = omp_get_wtime();
    time_cml2 = end_cml2 - start_cml2;

  }
  #else
  {
    start_cml2 = clock();
    mutual_links = count_mutual_links2(N,N_links, row_ptr, col_idx, num_involments);
    end_cml2 = clock();
    time_cml2 = (double) (end_cml2 - start_cml2)/CLOCKS_PER_SEC;

  }
  #endif
  printf("mutual links: %d\n", mutual_links);

 	// Free the slaves
 	free(row_ptr);
 	free(col_idx);

 	top_n_webpages(N, num_involments, N);

 	free(num_involments);

  FILE *fp;



 	return EXIT_SUCCESS;

}
