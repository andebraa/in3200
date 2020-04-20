#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
#include <time.h>

// skips a single line in the input
int skip_lines(FILE *fp, const int count) {
	for (int i = 0; i < count; i++) {
		for (int c = fgetc(fp); c != '\n' && c != EOF; c = fgetc(fp)) {}
	}
	return 0;
}


void read_graph_from_file1(char *filename, int *N, char ***table2D){

	FILE *ptr;

	ptr = fopen(filename, "r");

	skip_lines(ptr, 2);
	int N_links = 0;

	fscanf(ptr, "%*s %*s %d %*s %d /n", N, &N_links); //reading third line, extracting nodes, edges
	printf("nodes: %d, edges: %d \n", *N, N_links);//N: nodes (webpages)
	skip_lines(ptr, 1);


	(*table2D) = calloc(*N, sizeof(char*)); //making 2D array
	for(int i = 0; i < (*N); i++){
	(*table2D)[i] = calloc(*N, sizeof(char));
	}

	int from = 0;
	int to = 0;
	for(int i = 0; i < (N_links); i++){ //looping through all edges (links)
		fscanf(ptr, "%d %d", &from, &to);
		(*table2D)[to][from] = 1;
	}

	fclose(ptr);
}//end read_graph_from_file1
