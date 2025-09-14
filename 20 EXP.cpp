#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, writeBlock;
int data = 0;
int readersCount = 0;

void* reader(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < 10; i++) {
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&writeBlock); // First reader blocks writer
        }
        sem_post(&mutex);

        // Reading operation
        printf("Reader %d reads data: %d\n", id, data);
        usleep(100000); // simulate read delay

        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&writeBlock); // Last reader releases writer
        }
        sem_post(&mutex);

        usleep(100000); // simulate time between reads
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < 10; i++) {
        sem_wait(&writeBlock);

        // Writing operation
        data++;
        printf("Writer %d writes data: %d\n", id, data);
        usleep(150000); // simulate write delay

        sem_post(&writeBlock);

        usleep(100000); // simulate time between writes
    }
    return NULL;
}

int main() {
    pthread_t readerThreads[2], writerThreads[1];
    int rIDs[2] = {1, 2};
    int wID = 1;

    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    // Create reader threads
    for (int i = 0; i < 2; i++)
        pthread_create(&readerThreads[i], NULL, reader, &rIDs[i]);

    // Create writer thread
    pthread_create(&writerThreads[0], NULL, writer, &wID);

    // Wait for threads to finish
    for (int i = 0; i < 2; i++)
        pthread_join(readerThreads[i], NULL);
    pthread_join(writerThreads[0], NULL);

    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}

