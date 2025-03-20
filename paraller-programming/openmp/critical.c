#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){
  int *tab;
  int i;
  int seed = 0;

  #pragma omp parallel shared(tab) private(i, seed)
  {
    // useless single but just to show the concept 
    #pragma omp single
    {
      tab = malloc(10*sizeof(int*));
    }

    seed = omp_get_thread_num() + time(NULL);
    srand(seed);

    #pragma omp barrier

    #pragma omp critical
    {
      printf("Thread %d\n", omp_get_thread_num());
      for (i=0; i<10; i++){
        printf("%d = %d;", i, tab[i]);
        tab[i] = rand();
      } 
      printf("\n");
    }
  }
  return EXIT_SUCCESS;
}
