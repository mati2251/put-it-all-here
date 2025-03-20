#pragma once
#include <mpi.h>
#include "global.h"

struct packet {
  int lamport_clock;
  int rank;
  int data;
};

int compare_packet(const void *a, const void *b);

void init_packet_type();

int get_packet(struct packet *message, int tag);

struct packet send_packet_with_data(int from, int to, int tag, int data);

struct packet send_packet(int from, int to, int tag);

struct packet brodcast_packet(int tag, int from, int size);

struct packet brodcast_packet_with_data(int tag, int from, int size, int data); 

void internal_event();

int get_lamport_clock();
