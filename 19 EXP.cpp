#include <stdio.h>
#include <pthread.h>

// Shared variable
int counter = 0;
pthread_mutex_t mutex;

// Function executed by threads
void* threadFunction(void* arg) {
    for (int i = 0; i < 1000000; ++i) {
        pthread_mutex_lock(&mutex);
        counter++;  // Critical section
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&thread1, NULL, threadFunction, NULL);
    pthread_create(&thread2, NULL, threadFunction, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the final counter value
    printf("Final counter value: %d\n", counter);

    return 0;
}

