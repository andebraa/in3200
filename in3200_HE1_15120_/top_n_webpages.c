#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"
#include <time.h>

struct webpage_struct{
  int involments;
  int index;
};

int webpage_sort(const void *a, const void *b){
  struct webpage_struct pa = *((struct webpage_struct *)a);
	struct webpage_struct pb = *((struct webpage_struct *)b);

  return pa.involments - pb.involments;
}


void top_n_webpages(int num_webpages, int *num_involments, int n){

  struct webpage_struct *webpages = calloc(num_webpages, sizeof(*webpages));
  for(int i = 0; i < num_webpages; i++){ //making struct of paired
    webpages[i].involments = num_involments[i]; // webpages and webpage number
    webpages[i].index = i;
    //printf("%d %d\n", webpages[i].involments, webpages[i].index);
  }

  qsort(webpages, num_webpages, sizeof(*webpages), webpage_sort);

}//end top_n_webpages
