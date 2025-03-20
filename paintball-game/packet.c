#include "packet.h"
#include "log.h"
#include <pthread.h>
#include <stddef.h>

int lamport_clock = 0;
pthread_mutex_t clock_mutex;
pthread_mutex_t send_mutex;
MPI_Datatype MPI_PACKET;

int compare_packet(const void *a, const void *b) {
  struct packet *packet_a = (struct packet *)a;
  struct packet *packet_b = (struct packet *)b;
  if (packet_a->lamport_clock == packet_b->lamport_clock) {
    return packet_a->rank - packet_b->rank;
  }
  return packet_a->lamport_clock - packet_b->lamport_clock;
}

void init_packet_type() {
  int blocklengths[3] = {1, 1, 1};
  MPI_Datatype typy[3] = {MPI_INT, MPI_INT, MPI_INT};

  MPI_Aint offsets[3];
  offsets[0] = offsetof(struct packet, lamport_clock);
  offsets[1] = offsetof(struct packet, rank);
  offsets[2] = offsetof(struct packet, data);

  MPI_Type_create_struct(3, blocklengths, offsets, typy, &MPI_PACKET);

  MPI_Type_commit(&MPI_PACKET);
}

int get_packet(struct packet *message, int tag) {
  MPI_Status status;
  MPI_Recv(message, 1, MPI_PACKET, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD,
           &status);
  lamport_clock =
      (message->lamport_clock > lamport_clock ? message->lamport_clock
                                              : lamport_clock) +
      1;
  return status.MPI_TAG;
}

struct packet send_packet_with_data(int from, int to, int tag, int data) {
  struct packet message;
  message.data = data;
  pthread_mutex_lock(&clock_mutex);
  lamport_clock++;
  pthread_mutex_unlock(&clock_mutex);
  message.lamport_clock = lamport_clock;
  message.rank = from;
  pthread_mutex_lock(&send_mutex);
  MPI_Send(&message, 1, MPI_PACKET, to, tag, MPI_COMM_WORLD);
  pthread_mutex_unlock(&send_mutex);
  return message;
}

struct packet send_packet(int from, int to, int tag) {
  return send_packet_with_data(from, to, tag, 0);
}

struct packet brodcast_packet(int tag, int from, int size) {
  return brodcast_packet_with_data(tag, from, size, 0);
}

struct packet brodcast_packet_with_data(int tag, int from, int size, int data) {
  struct packet message;
  message.data = data;
  pthread_mutex_lock(&clock_mutex);
  lamport_clock++;
  pthread_mutex_unlock(&clock_mutex);
  message.lamport_clock = lamport_clock;
  message.rank = from;
  pthread_mutex_lock(&send_mutex);
  for (int i = 0; i < size; i++) {
    debug("Send brodcast to %d", i);
    MPI_Send(&message, 1, MPI_PACKET, i, tag, MPI_COMM_WORLD);
  }
  pthread_mutex_unlock(&send_mutex);
  return message;
}

void internal_event() {
  pthread_mutex_lock(&clock_mutex);
  lamport_clock++;
  pthread_mutex_unlock(&clock_mutex);
}

int get_lamport_clock() {
  pthread_mutex_lock(&clock_mutex);
  int clock = lamport_clock;
  pthread_mutex_unlock(&clock_mutex);
  return clock;
}
