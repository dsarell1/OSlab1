#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define errExit(msg) 
#define BUF_SIZE 2  // Max size for Buffer 

// Shared memory object
struct shmbuf {
    sem_t  notEmpty, notFull;           // semaphores 
    size_t cnt;             // Number of bytes used in buffer
    int buffer[BUF_SIZE];   // Table. The data being stored.
};
#endif