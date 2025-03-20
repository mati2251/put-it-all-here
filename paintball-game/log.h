#pragma once
#include <stdio.h>

#ifdef DEBUG
#define debug(FORMAT, ...)                                                     \
  printf("%c[%d;%dm [%d][🕒%d]: " FORMAT "%c[%d;%dm\n", 27,                    \
         (1 + (rank / 7)) % 2, 31 + (6 + rank) % 7, rank,    \
         lamport_clock, ##__VA_ARGS__, 27, 0, 37);
#else
#define debug(...) ;
#endif

#define println(FORMAT, ...)                                                   \
  printf("%c[%d;%dm [%d][🕒%d]: " FORMAT "%c[%d;%dm\n", 27,                    \
         (1 + (rank / 7)) % 2, 31 + (6 + rank) % 7, rank,    \
         lamport_clock, ##__VA_ARGS__, 27, 0, 37);

