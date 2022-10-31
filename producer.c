// Dylan Sarell
// 10/21/22
// Producer Process

#include "shared.h"

int main() { 
    // Random Number Generator
    time_t t;   
    srand(time(&t));

    // Create shared memory object and set its size to the size of our structure. 
    char * shmpath = "/&";
    int fd = shm_open(shmpath, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fd == -1) errExit("shm_open");
    if (ftruncate(fd, sizeof(struct shmbuf)) == -1) errExit("ftruncate");

    // Map the object into the caller's address space.
    struct shmbuf *shmp = mmap(NULL, sizeof(struct shmbuf), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shmp == MAP_FAILED) errExit("mmap");

    // semaphore initialization
    if (sem_init(&shmp->notEmpty, 0, 0) == -1) errExit("sem_init-notEmpty");
    if (sem_init(&shmp->notFull, 0, 2) == -1) errExit("sem_init-notFull");

    if (sem_wait(&shmp->notFull) == -1) // sem_wait or wait(). Waits until buffer is not Full.
        errExit("sem_wait");

    shmp->cnt = 0;
    printf("\n");

    // for loop produces 2 numbers and copies it to Shared memory Object
    for (int o = 0; o < BUF_SIZE; ++o) { 
        // produce
        int x = rand() % 100;
        int * ptr = &x;
        // add to buffer and copy it to the shared memory object
        shmp->buffer[o] = x;
        shmp->cnt = o;
        int z = o + 1;
        int * ptr2 = &z;

        memcpy(&shmp->buffer[o], ptr, 1); 
        memcpy(&shmp->cnt, ptr2, 1);
        printf("Producer Produces item: %d\n", shmp->buffer[o]);
    }

    if (sem_post(&shmp->notEmpty) == -1) // sem_post or signal(). Signals that the buffer is not Empty to Consumer Process.
        errExit("sem_post");

    exit(EXIT_SUCCESS);
}