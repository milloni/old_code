#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define UNUSED(x) (void)(x)
#define N (2)

char **ptr;

void fatal(const char *s) {
    perror(s);
    exit(1);
}

void *thread_run(void *arg) {
    UNUSED(arg);

    int myid = (int)arg;
    static int cnt = 0;
    printf("[%d]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
    return NULL;
}

int main(void) {
    pthread_t tid;
    char *msgs[N] = {
        "Hello from foo",
        "Hello from bar"
    };
    ptr = msgs;

    for (int i = 0; i < N; i++) {
        if (pthread_create(&tid, NULL, thread_run, (void *)i) != 0) {
            fatal("pthread_create:");
        }
    }

    pthread_exit(0);
}

