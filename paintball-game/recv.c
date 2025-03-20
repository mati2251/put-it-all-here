#include "recv.h"
#include "global.h"
#include "log.h"
#include "packet.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

int winner = -1;
int winner_score = -1;

void *replay_thread() {
  struct packet message;
  while (true) {
    int tag = get_packet(&message, MPI_ANY_TAG);
    switch (tag) {
    case PAIR_REQUEST: {
      pthread_mutex_lock(&request_pair_queue_mutex);
      if (request_pair_queue_size < size * 2) {
        request_pair_queue[request_pair_queue_size] = message;
        request_pair_queue_size++;
      }
      pthread_mutex_unlock(&request_pair_queue_mutex);
      send_packet(rank, message.rank, PAIR_RESPONSE);
      debug("Recieve pair request. Sent pair response to %d", message.rank);
      break;
    }
    case PAIR_RESPONSE: {
      pthread_mutex_lock(&pair_response_mutex);
      pthread_mutex_lock(&pair_request_mutex);
      if (message.lamport_clock < pair_request.lamport_clock) {
        println("Response has lower clock than request %d < %d",
                message.lamport_clock, pair_request.lamport_clock);
        exit(0);
      }
      pthread_mutex_unlock(&pair_request_mutex);
      pair_response_count--;
      pthread_cond_signal(&pair_response_cond);
      debug("Recieve pair response from %d", message.rank);
      pthread_mutex_unlock(&pair_response_mutex);
      break;
    }
    case GUN_REQUEST: {
      if (message.rank == rank) {
        break;
      }
      pthread_mutex_lock(&gun_state_mutex);
      int state = gun_access_state;
      pthread_mutex_unlock(&gun_state_mutex);
      if ((state == HELD) || (state == PLAN && gun_request.lamport_clock <
                                                   message.lamport_clock)) {
        pthread_mutex_lock(&request_gun_queue_mutex);
        request_gun_queue[request_gun_queue_size] = message;
        request_gun_queue_size++;
        pthread_mutex_unlock(&request_gun_queue_mutex);
      } else {
        send_packet(rank, message.rank, GUN_RESPONSE);
      }
      break;
    }
    case GUN_RESPONSE: {
      pthread_mutex_lock(&gun_response_mutex);
      debug("Recieve gun response from %d", message.rank);
      gun_response_count--;
      pthread_cond_signal(&gun_response_cond);
      pthread_mutex_unlock(&gun_response_mutex);
      break;
    }
    case PAIR_RESULT: {
      pthread_mutex_lock(&pair_mutex);
      println("Recieve result %d from %d", 1 - message.data % 2, message.rank);
      score += 1 - message.data % 2;
      pthread_cond_signal(&pair_cond);
      pthread_mutex_unlock(&pair_mutex);
      break;
    }
    case END_REQUEST: {
      debug("Recieve end request from %d", message.rank);
      end_count--;
      if (message.data > winner_score) {
        winner_score = message.data;
        winner = message.rank;
      } else if (message.data == winner_score) {
        if (message.rank < winner) {
          winner = message.rank;
        }
      }
      if (end_count == 0) {
        println("Winner is %d with score %d", winner, winner_score);
        pthread_exit(NULL);
      }
      break;
    }
    }
  }
  return NULL;
}
