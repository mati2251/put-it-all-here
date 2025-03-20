#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define PASSENGERS_SIZE 24
#define TROLLEY_SIZE 4

int iterator = 0;
int current_trolley = 0;
pthread_mutex_t trolley_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cnd_trolley = PTHREAD_COND_INITIALIZER, cnd_wait_to_start = PTHREAD_COND_INITIALIZER;

void *passenger() {
    int id = iterator++;
    printf("Passenger %d wait for trolley\n", id);
    pthread_mutex_lock(&trolley_mutex);
    while (current_trolley == TROLLEY_SIZE) {
        pthread_cond_wait(&cnd_trolley, &trolley_mutex);
    }
    printf("Passenger %d sit down in trolley\n", id);
    current_trolley++;
    if (current_trolley == TROLLEY_SIZE) {
        printf("Trolley start\n");
        sleep(2);
        pthread_cond_broadcast(&cnd_wait_to_start);
        printf("Passenger %d exit trolley \n", id);
        current_trolley = 0;
        printf("Trolley already to start\n");
        pthread_cond_broadcast(&cnd_trolley);
    } else {
        printf("Passenger %d wait for start\n", id);
        printf("Passenger %d exit trolley \n", id);
        pthread_cond_wait(&cnd_wait_to_start, &trolley_mutex);
    }
    pthread_mutex_unlock(&trolley_mutex);
    return NULL;
}

int main() {
    pthread_t ptid[PASSENGERS_SIZE];
    for (int i = 0; i < PASSENGERS_SIZE; i++) {
        pthread_create(&ptid[i], NULL, &passenger, NULL);
    }
    for (int i = 0; i < PASSENGERS_SIZE; i++) {
        pthread_join(ptid[i], NULL);
    }
    return 0;
}

