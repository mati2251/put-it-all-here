

#include <stdio.h>
int main(int argc, char *argv[]) {
  int n = 8;
  int counter = 0;

  #pragma omp parallel num_threads(n)
  {
    for (int i = 0; i < 5; i++) {
      #pragma omp atomic 
      counter++; 
    } 
  }
  printf("counter = %d\n", counter);
  counter = 0;
  #pragma omp parallel num_threads(n)
  {
    for (int i = 0; i < 5; i++) {
      counter++; 
    } 
  }
  printf("counter = %d\n", counter);
}
