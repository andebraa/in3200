
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
#include <time.h>
#include "read_graph_from_file1.h"


struct pairs{
	int from;
	int to;
};

int pair_comp(const void *a, const  void * b) {
	struct pairs pa = *((struct pairs *)a);
	struct pairs pb = *((struct pairs *)b);
	//following if test makes sure sorting is both by colloumn and row!
	//if two to's are siliar then the froms are compared!
	if (pa.to == pb.to){return pa.from - pb.from;}
	else{ return pa.to - pb.to;}
}


void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx){


	FILE *ptr;
	//str string;
	ptr = fopen(filename, "r");

	skip_lines(ptr, 2);

	fscanf(ptr, "%*s %*s %d %*s %d", N, N_links);
	skip_lines(ptr, 2);


	struct pairs *rowcol = calloc(*N_links, sizeof(*rowcol));
	int from = 0;
	int to = 0;
	int N_self_links=0;

	//array to hold the number of elements on a given row
	int *row_num = calloc(*N+1, sizeof(int));
	for(int i = 0; i < *N_links; i++){ //looping through all edges (links)

		fscanf(ptr, "%d %d \n", &from, &to);
		if(from == to){
			N_self_links ++; //this test will leave N_self_links number of zeros in file
		}else{
			rowcol[i].from = from;
			rowcol[i].to = to;
			row_num[to] ++;
		}
	}//end for


	qsort(rowcol, *N_links, sizeof(*rowcol), pair_comp);

	printf("number of self links %d\n", N_self_links);
	// If there are E edges, there are N_links 1s in the matrix.
	int *col = calloc(*N_links - N_self_links, sizeof(int));
	//files index from 0 to N-1, but first element in row_ptr
	//must be 0. this is why row is N+1 long, where the first is always 0
	int *row = calloc((*N+2), sizeof(int));


	for(int i = 0;i < ((*N+1)); i++){
		row[i+1] = (row[i] + row_num[i]); //wish for the first element to remain zero
		//printf("row_ptr: %d \n",row[i]);
	}
	for(int i = 0; i < (*N_links - N_self_links); i++){

		col[i] = rowcol[N_self_links + i].from;
		//printf("col_idx: %d \n", col[i]);
	}


	*row_ptr = row;
	*col_idx = col;
	fclose(ptr);
	free(rowcol);
	free(row_num);

}//end read_graph_from_file2
