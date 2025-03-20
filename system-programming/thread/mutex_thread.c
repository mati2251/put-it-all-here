#include <pthread.h>
#include <stdio.h>

#define BUF_SIZE 100
// local variable initialized for thread
// __thread int g = 0;
// global variable initialized for variable
int buf[BUF_SIZE];
int it_consument = 0;
int it_producer = 0;
static pthread_cond_t cnd_empty = PTHREAD_COND_INITIALIZER,
                      cnd_full = PTHREAD_COND_INITIALIZER;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

// Thread function with critical section
/*
void *function() {
  // global variable for thread
  volatile static int l;
  // local variable for thread
  int l;
  pthread_mutex_lock(&m);
  l++;
  g++;
  printf("g=%d, l=%d \n", g, l);
  fflush(stdout);
  pthread_mutex_unlock(&m);
  return NULL;
}
*/

void put(int value) {
  pthread_mutex_lock(&m);
  while (it_consument > it_producer) {
    pthread_cond_wait(&cnd_empty, &m);
  }
  buf[it_producer % BUF_SIZE] = value;
  it_producer++;
  pthread_cond_signal(&cnd_full);
  pthread_mutex_unlock(&m);
}

int get() {
  pthread_mutex_lock(&m);
  while (it_consument >= it_producer) {
    pthread_cond_wait(&cnd_empty, &m);
  }
  it_consument++;
  int value = buf[(it_consument - 1) % BUF_SIZE];
  pthread_cond_signal(&cnd_full);
  pthread_mutex_unlock(&m);
  return value;
}

void *prod() {
  for (int i = 0; i < 100; i++) {
    put(i);
  }
  return NULL;
}

void *cons() {
  for (int i = 0; i < 100; i++) {
    printf("%d\n", get());
  }
  return NULL;
}

int main() {
  pthread_t ptid;
  pthread_create(&ptid, NULL, &prod, NULL);
  pthread_create(&ptid, NULL, &cons, NULL);
  pthread_exit(NULL);
}