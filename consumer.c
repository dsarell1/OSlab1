// Dylan Sarell
// 10/21/22
// Consumer Process

#include "shared.h"

int main() {

    char * shmpath = "/&";
    int fd = shm_open(shmpath, O_RDWR, 0);

    if (fd == -1) errExit("shm_open");
    if (ftruncate(fd, sizeof(struct shmbuf)) == -1) errExit("ftruncate");

    struct shmbuf *shmp = mmap(NULL, sizeof(struct shmbuf), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shmp == MAP_FAILED) errExit("mmap");

    if (sem_wait(&shmp->notEmpty) == -1) // sem_wait or wait(). Waits until the Buffer is not Empty.
        errExit("sem_post");

    // Copy data from shared memory object to output it. 
    for (int a = 0; a < shmp->cnt; ++a) {
        // Remove from buffer
        int y = shmp->buffer[a];
        printf("Consumer Consumes item: ");
        // Consume the number. (Output it)
        sleep(2);
        printf("%d\n", y);
    }
    if (sem_post(&shmp->notFull) == -1) // sem_post or Signal(). Signals that the Buffer is not Full.
        errExit("sem_wait");

    shm_unlink(shmpath);

    exit(EXIT_SUCCESS);
}