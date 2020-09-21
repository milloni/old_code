#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define UNUSED(x) (void)(x)

void fatal(const char *s) {
    perror(s);
    exit(1);
}

void *thread_run(void *arg) {
    UNUSED(arg);

    while (true) {
        sleep(1);
    }
}

int main(void) {
    pthread_t tid;
    if (pthread_create(&tid, NULL, thread_run, NULL) != 0) {
        fatal("pthread_create");
    }

    sleep(5);
    if (pthread_cancel(tid) != 0) {
        fatal("pthread_cancel");
    }
    if (pthread_join(tid, NULL) != 0) {
        fatal("pthread_join");
    }

    return 0;
}

