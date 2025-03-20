#pragma once

#define PAIR_REQUEST 0
#define PAIR_RESPONSE 1
#define PAIR_RESULT 2
#define END_REQUEST 3
#define GUN_REQUEST 4
#define GUN_RESPONSE 5

#define PLAN 0
#define HELD 1
#define RELEASED 2

#define CYCLE_SIZE 3
#define GUNS_COUNT 2 

#include "packet.h"
#include <pthread.h>

extern MPI_Datatype MPI_PACKET;

extern int rank;
extern int size;
extern int score;

extern int lamport_clock;
extern int end_count;

extern struct packet *request_pair_queue;
extern int request_pair_queue_size;
extern pthread_mutex_t request_pair_queue_mutex;

extern int pair_response_count;
extern pthread_mutex_t pair_response_mutex;
extern pthread_cond_t pair_response_cond;

extern struct packet pair_request;
extern pthread_mutex_t pair_request_mutex;

extern int gun_access_state;
extern pthread_mutex_t gun_state_mutex;

extern int gun_response_count;
extern pthread_mutex_t gun_response_mutex;
extern pthread_cond_t gun_response_cond;

extern struct packet *request_gun_queue;
extern int request_gun_queue_size;
extern pthread_mutex_t request_gun_queue_mutex;

extern struct packet gun_request;
extern pthread_mutex_t gun_request_mutex;

extern pthread_mutex_t pair_mutex;
extern pthread_cond_t pair_cond;

