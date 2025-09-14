#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>   // for sleep()

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE] = {0}; // initialize to empty
sem_t empty, full;
pthread_mutex_t mutex;

int produced_items = 0, consumed_items = 0;

void* producer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (produced_items >= MAX_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        sem_wait(&empty);

        pthread_mutex_lock(&mutex);
        // Critical section: add item to buffer
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] == 0) {
                buffer[i] = produced_items + 1;
                printf("Produced: %d\n", buffer[i]);
                produced_items++;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);

        sem_post(&full);
        sleep(1); // simulate delay
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (consumed_items >= MAX_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        sem_wait(&full);

        pthread_mutex_lock(&mutex);
        // Critical section: remove item from buffer
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] != 0) {
                printf("Consumed: %d\n", buffer[i]);
                buffer[i] = 0;
                consumed_items++;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);

        sem_post(&empty);
        sleep(2); // simulate delay
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}


