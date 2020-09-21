#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define UNUSED(x) (void)(x)
#define N (3)

static pthread_mutex_t mutex;
static pthread_cond_t cond;
static int nthreads;
static int barriercnt = 0;

void _f(const char *msg) {
    perror(msg);
    exit(1);
}

void my_pthread_mutex_init(pthread_mutex_t *restrict mutex,
        const pthread_mutexattr_t *restrict attr) {
    if (pthread_mutex_init(mutex, attr) != 0) {
        _f("pthread_mutex_init");
    }
}

void my_pthread_cond_init(pthread_cond_t *cond,
        const pthread_condattr_t *restrict attr) {
    if (pthread_cond_init(cond, attr) != 0) {
        _f("pthread_cond_init");
    }
}

void barrier(void) {
    if (pthread_mutex_lock(&mutex) != 0) _f("pthread_mutex_lock");
    if (++barriercnt == nthreads) {
        barriercnt = 0;
        if (pthread_cond_broadcast(&cond) != 0) _f("pthread_cond_broadcast");
    } else {
        if (pthread_cond_wait(&cond, &mutex) != 0) _f("pthread_cond_wait");
    }
    if (pthread_mutex_unlock(&mutex) != 0) _f("pthread_mutex_unlock");

    printf("Thread %lu executing barrier()\n", pthread_self());
}

void *thread_run(void *arg) {
    UNUSED(arg);

    for (int i = 0; i < 5; i++) barrier();

    return NULL;
}

int main(void) {
    nthreads = N;
    my_pthread_mutex_init(&mutex, NULL);
    my_pthread_cond_init(&cond, NULL);

    pthread_t tids[N];
    for (int i = 0; i < N; i++) {
        if (pthread_create(&tids[i], NULL, thread_run, NULL) != 0) {
            _f("pthread_create");
        }
    }
    for (int i = 0; i < N; i++) {
        if (pthread_join(tids[i], NULL) != 0) {
            _f("pthread_join");
        }
    }

    return 0;
}

