#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  double start;
  double end;
  int i, n = 0;
  int sum = 0;

  if (argc < 2) {
    printf("Usage: %s n\n", argv[0]);
    return EXIT_FAILURE;
  }

  n = atoi(argv[1]);

  int *tab = malloc(n * sizeof(int));
  unsigned int seed = time(NULL) * (getpid() + 1);
  srand(seed);
  for (i = 0; i < n; i++) {
    tab[i] = rand();
  }

  start = omp_get_wtime();
  for (i = 0; i < n; i++) {
    sum += tab[i];
  }
  end = omp_get_wtime();
  printf("Imperative | %d | %d | %f |\n", sum, n, end - start);

  sum = 0;
  start = omp_get_wtime();
#pragma omp parallel for reduction(+:sum) private(i)
  for (i = 0; i < n; i++) {
    sum += tab[i];
  }
  end = omp_get_wtime();
  printf("Parraller | %d | %d | %f |\n", sum, n, end - start);

  free(tab);
  return EXIT_SUCCESS;
}
