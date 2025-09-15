#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* func(void* arg) {
    printf("Inside the thread\n");
    pthread_exit(NULL);   // ends this thread
}

void fun() {
    pthread_t ptid;
    int ret;

    // create a thread
    ret = pthread_create(&ptid, NULL, func, NULL);
    if (ret != 0) {
        printf("Thread creation failed\n");
        exit(1);
    }

    printf("This line may be printed before thread terminates\n");

    // compare thread IDs
    if (pthread_equal(ptid, pthread_self())) {
        printf("Threads are equal\n");
    } else {
        printf("Threads are not equal\n");
    }

    // wait for the thread to finish
    pthread_join(ptid, NULL);

    printf("This line will be printed after thread ends\n");
}

int main() {
    fun();
    return 0;
}

