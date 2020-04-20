#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
#include "string.h"

#include "test.h"
#include "read_graph_from_file1.h"
#include "read_graph_from_file2.h"
#include "count_mutual_links1.h"
#include "count_mutual_links2.h"
#include "top_n_webpages.h"




int main(int argc, char *argv[]) {


	  if (argc != 2) {
	    printf("Usage: %s <data file>\n", argv[0]);
	    return EXIT_FAILURE;
	  }

	int N, *num_involments; //N: nodes, N_links: edges
	char* filename = "data_50000.txt";


  //2D TABLE AND CM_MUTUAL1


	char **table2D;

	read_graph_from_file1(filename, &N, &table2D);

/* //if running a small data file, for example the data set given in the problem set then this print is a nice way of confirming that this works
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			printf(" %d ", table2D[i][j]);
		}
		printf("\n");
	}
*/

	num_involments = calloc(N, sizeof(int)); //number of outbound links
	if (num_involments == NULL)  {
		perror("couldn't calloc");
		exit(-1);

	}
	int cm_links1 = count_mutual_links1(N, table2D, num_involments);
	printf("mutual links: %d\n", cm_links1);

	for (int i = 0; i < N; i++) {
		free(table2D[i]);
	}
	free(table2D);
	free(num_involments);



	//COMPRESSED ROWS!


	int *row_ptr, *col_idx, N_links, mutual_links;

	read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);

	num_involments = calloc(N, sizeof(int)); //number of outbound links
	if (num_involments == NULL)  {
		perror("couldn't calloc");
		exit(-1);

	}


	mutual_links = count_mutual_links2(N,N_links, row_ptr, col_idx, num_involments);
	printf("mutual links: %d\n", mutual_links);

	// Free the slaves
	free(row_ptr);
	free(col_idx);

	top_n_webpages(N, num_involments, N);

	free(num_involments);


	int test_rez = test(argc, argv);

	return EXIT_SUCCESS;
} // end main
