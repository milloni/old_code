#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define UNUSED(x) (void)(x)

void _f(const char *msg) {
    perror(msg);
    exit(1);
}

void my_sem_wait(sem_t *sem) {
    while (sem_wait(sem) != 0) {
        if (errno == EINVAL) _f("sem_wait");
        else if (errno == EINTR) continue;
    }
}

void my_sem_post(sem_t *sem) {
    if (sem_post(sem) != 0) _f("sem_post");
}

void my_sem_init(sem_t *sem, int pshared, unsigned int value) {
    if (sem_init(sem, pshared, value) != 0) _f("sem_init");
}

int main(void) {
    return 0;
}

