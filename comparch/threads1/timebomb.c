#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <sys/time.h>

#define UNUSED(x) (void)(x)
#define TIMEOUT (5)

pthread_cond_t cond;
pthread_mutex_t mutex;
pthread_t tid;

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

struct timespec *maketimeout(struct timespec *tp, int secs) {
    struct timeval now;
    gettimeofday(&now, NULL);
    tp->tv_sec = now.tv_sec + secs;
    tp->tv_nsec = now.tv_usec * 1000;
    return tp;
}

void *thread_run(void *arg) {
    UNUSED(arg);

    getchar();
    if (pthread_mutex_lock(&mutex) != 0) _f("pthread_mutex_lock");
    if (pthread_cond_signal(&cond) != 0) _f("pthread_cond_signal");
    if (pthread_mutex_unlock(&mutex) != 0) _f("pthread_mutex_unlock");

    return NULL;
}

int main(void) {
    my_pthread_cond_init(&cond, NULL);
    my_pthread_mutex_init(&mutex, NULL);
   
    int rc;
    pthread_t tid;
    struct timespec timeout;
    if (pthread_mutex_lock(&mutex) != 0) _f("pthread_mutex_lock");
    if (pthread_create(&tid, NULL, thread_run, NULL) != 0) _f("pthread_create");
    for (int i = 0; i < TIMEOUT; i++) {
        printf("BEEP!\n");
        rc = pthread_cond_timedwait(&cond, &mutex, maketimeout(&timeout, 1));
        if (rc != ETIMEDOUT) {
            printf("WHEW\n");
            exit(0);
        }
    }

    printf("BOOM!\b\b\b\n");
    return 0;
}

