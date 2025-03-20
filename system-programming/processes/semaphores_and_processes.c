#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

#define MAX 10

static struct sembuf buf;

struct buf_and_indexes {
  int buf[MAX];
  int index_read;
  int index_write;
};

void down(int semid, int semnum) {
  buf.sem_num = semnum;
  buf.sem_op = -1;
  buf.sem_flg = 0;
  if (semop(semid, &buf, 1) == -1) {
    perror("Podnoszenie semafora");
    exit(1);
  }
}

void up(int semid, int semnum) {
  buf.sem_num = semnum;
  buf.sem_op = 1;
  buf.sem_flg = 0;
  if (semop(semid, &buf, 1) == -1) {
    perror("Opuszczenie semafora");
    exit(1);
  }
}

void producer(int semid, struct buf_and_indexes *data) {
  while (data->index_write < 100) {
    up(semid, 2);
    down(semid, 0);
    data->buf[data->index_write % MAX] = data->index_write % MAX;
    up(semid, 1);
    down(semid, 2);
    data->index_write++;
  }
}

void consumer(int semid, struct buf_and_indexes *data) {
  while (data->index_read < 100) {
    up(semid, 3);
    down(semid, 1);
    printf("Numer: %5d   Wartosc: %d\n", data->index_read,
           data->buf[data->index_read % MAX]);
    up(semid, 0);
    down(semid, 3);
    data->index_read++;
  }
}

int main() {
  int shmid, semid;
  struct buf_and_indexes *ptr;
  semid = semget(45282, 4, IPC_CREAT | 0600);
  if (semid == -1) {
    perror("Utworzenie tablicy semaforow");
    exit(1);
  }
  if (semctl(semid, 0, SETVAL, (int)1) == -1) {
    perror("Nadanie wartosci semaforowi 0");
    exit(1);
  }
  if (semctl(semid, 1, SETVAL, (int)0) == -1) {
    perror("Nadanie wartosci semaforowi 1");
    exit(1);
  }
  shmid = shmget(45282, sizeof(struct buf_and_indexes), IPC_CREAT | 0600);
  if (shmid == -1) {
    perror("Utworzenie segmentu pamieci wspoldzielonej");
    exit(1);
  }

  ptr = (struct buf_and_indexes *)shmat(shmid, NULL, 0);
  ptr->index_read = 0;
  ptr->index_write = 0;
  if (ptr == NULL) {
    perror("Przylaczenie segmentu pamieci wspoldzielonej");
    exit(1);
  }
  fork();
  if (fork() == 0) {
    producer(semid, ptr);
  } else {
    consumer(semid, ptr);
  }
}