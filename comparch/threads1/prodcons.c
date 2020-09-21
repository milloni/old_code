#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define UNUSED(x) (void)(x)
#define NITERS (5)

typedef struct _shared_t {
    int buf;
    sem_t full, empty;
} shared_t;

shared_t shared;

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

void *producer(void *arg) {
    UNUSED(arg);

    int item = 0;
    for (int i = 0; i < NITERS; i++) {
        item = i;
        printf("[Producer] Produced %d\n", item);
        
        my_sem_wait(&shared.empty);
        shared.buf = item;
        my_sem_post(&shared.full);
    }

    return NULL;
}

void *consumer(void *arg) {
    UNUSED(arg);

    int item = 0;
    for (int i = 0; i < NITERS; i++) {
        my_sem_wait(&shared.full);
        item = shared.buf;
        my_sem_post(&shared.empty);

        printf("[Consumer] Consumed %d\n", item);
    }

    return NULL;
}

int main(void) {
    pthread_t prod_tid, cons_tid;
    my_sem_init(&shared.empty, 0, 1);
    my_sem_init(&shared.full, 0, 0);

    if (pthread_create(&prod_tid, NULL, producer, NULL) != 0) {
        _f("pthread_create");
    } 
    if (pthread_create(&cons_tid, NULL, consumer, NULL) != 0) {
        _f("pthread_create");
    }
    if (pthread_join(prod_tid, NULL) != 0) _f("pthread_join");
    if (pthread_join(cons_tid, NULL) != 0) _f("pthread_join");
}

