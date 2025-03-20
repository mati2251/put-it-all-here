#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
  int tab[10];
  int i;
  int sum = 0, mul = 1;
  srand(time(NULL));
  for (i = 0; i < 10; i++) {
    tab[i] = rand() % 100;
  }

  #pragma omp parallel shared(tab, sum, mul) private(i)
  {
    #pragma omp sections
    {
      #pragma omp section
      for (i = 0; i < 10; i++)
        sum += tab[i];
      #pragma omp section
      for (i = 0; i < 10; i++)
        mul *= tab[i];
    }
  }
  
  printf("sum %d mul %d\n",sum, mul);
}
