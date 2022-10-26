// Dylan Sarell
// 10/21/22
// Producer Process

//#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // allows use of sleep() in linux
//#include "shared.hpp"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define THREAD_NUM 2

sem_t notEmpty, notFull;
int items = 0;
int buffer[2];


void *producer(void *arg) {
    while(1) {
        // produce
        int x = rand() % 100;
        // add to buffer
        sem_wait(&notFull); // sem_wait or wait()
        buffer[items] = x;
        items++;
        printf("Producer Produces item: \n");
        sem_post(&notEmpty); // sem_post or signal()
    }
}
void* consumer(void * arg) {
    while(1) {
        int y;

        // Remove from buffer
        sem_wait(&notEmpty);
        y = buffer[items - 1];
        items--;
        printf("Consumer Consumes item: ");
        sem_post(&notFull);

        // Consume
        printf("%d\n", y);
        sleep(5);
    }
}

//int main(int argc, char* argv[]) {
int main() {   
    pthread_t th[THREAD_NUM];

    // semaphore initialization
    sem_init(&notEmpty, 0, 0);
    sem_init(&notFull, 0, 2);

    for (int i = 0; i < THREAD_NUM; i++) {
        if(i % 2 == 0) {
            if(pthread_create(&th[i], NULL, &producer, NULL) != 0) {
                perror("failed to create Thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) {
                perror("Failed to Create Thread");
            }
        }
    }
    for (int i = 0; i < THREAD_NUM; i++) {
        if(pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&notEmpty);
    sem_destroy(&notFull);
    return 0;
}