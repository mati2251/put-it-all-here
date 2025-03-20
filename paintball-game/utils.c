#include "utils.h"
#include "global.h"
#include "log.h"
#include "packet.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int pair() {
  internal_event();
  pthread_mutex_lock(&pair_response_mutex);
  pair_response_count = size;
  pthread_mutex_unlock(&pair_response_mutex);
  pthread_mutex_lock(&pair_request_mutex);
  pair_request = brodcast_packet(PAIR_REQUEST, rank, size);
  pthread_mutex_unlock(&pair_request_mutex);
  pthread_mutex_lock(&pair_response_mutex);
  while (pair_response_count > 0) {
    pthread_cond_wait(&pair_response_cond, &pair_response_mutex);
  }
  pthread_mutex_unlock(&pair_response_mutex);
  pthread_mutex_lock(&request_pair_queue_mutex);
  internal_event();
  qsort(request_pair_queue, request_pair_queue_size, sizeof(struct packet),
        compare_packet);
  int index = 0;
  for (int i = request_pair_queue_size - 1; i >= 0; i--) {
    if (request_pair_queue[i].rank == rank) {
      index = i;
      break;
    }
  }
  // print request_pair_queue
  // printf("Request pair queue %d: ", rank);
  // for (int i = 0; i < request_pair_queue_size; i++) {
  //   printf("%d ", request_pair_queue[i].rank);
  // }
  // printf("\n");
  int pair = -1;
  if (index % 2 == 1) {
    pair = request_pair_queue[index - 1].rank;
  }
  int old_size = request_pair_queue_size;
  request_pair_queue_size = request_pair_queue_size % 2;
  if (request_pair_queue_size > 0) {
    request_pair_queue[0] = request_pair_queue[old_size - 1];
  }
  pthread_mutex_unlock(&request_pair_queue_mutex);
  return pair;
}

void battle(int my_pair) {
  internal_event();
  if (my_pair == -1) {
    println("%d is waitnig for him pair. %d is victim", rank, rank)
        pthread_mutex_lock(&pair_mutex);
    pthread_cond_wait(&pair_cond, &pair_mutex);
    pthread_mutex_unlock(&pair_mutex);
  } else {
    println("%d is pared with %d. %d is killer.", rank, my_pair, rank);
    sleep(1);
    internal_event();
    int random = rand() % 2;
    score += random;
    if (random == 1) {
      println("%d defeated %d", rank, my_pair)
    } else {
      println("%d defeated %d", rank, my_pair)
    }
    send_packet_with_data(rank, my_pair, PAIR_RESULT, random);
  }
}

void gun_search() {
  println("%d is searching for a gun.", rank);
  pthread_mutex_lock(&gun_state_mutex);
  gun_access_state = PLAN;
  pthread_mutex_unlock(&gun_state_mutex);
  internal_event();
  pthread_mutex_lock(&gun_response_mutex);
  gun_response_count = size;
  pthread_mutex_unlock(&gun_response_mutex);
  gun_request = brodcast_packet(GUN_REQUEST, rank, size);
  pthread_mutex_lock(&gun_response_mutex);
  while (gun_response_count - GUNS_COUNT > 0) {
    debug("Wait for gun response. %d", gun_response_count);
    pthread_cond_wait(&gun_response_cond, &gun_response_mutex);
  }
  pthread_mutex_unlock(&gun_response_mutex);
  pthread_mutex_lock(&gun_state_mutex);
  gun_access_state = HELD;
  pthread_mutex_unlock(&gun_state_mutex);
  println("%d obtained a gun.", rank);
}

void gun_release() {
  println("%d released a gun.", rank);
  pthread_mutex_lock(&gun_state_mutex);
  gun_access_state = RELEASED;
  pthread_mutex_unlock(&gun_state_mutex);
  internal_event();
  pthread_mutex_lock(&request_gun_queue_mutex);
  for (int i = 0; i < request_gun_queue_size; i++) {
    debug("Send gun response to %d", request_gun_queue[i].rank)
        send_packet(rank, request_gun_queue[i].rank, GUN_RESPONSE);
  }
  request_gun_queue_size = 0;
  pthread_mutex_unlock(&request_gun_queue_mutex);
}
