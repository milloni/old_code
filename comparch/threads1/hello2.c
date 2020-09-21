#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define UNUSED(x) ((void)(x))

void fatal(const char *s) {
    perror(s);
    exit(1);
}

void *thread(void *vargp) {
    UNUSED(vargp);

    pthread_t tid = pthread_self();
    printf("Hello, my thread ID is: %lu\n", tid);
    return NULL;
}

int main(void) {
    pthread_t tid;
    if (pthread_create(&tid, NULL, thread, NULL) != 0) fatal("pthread_create");
    if (pthread_join(tid, NULL) != 0) fatal("pthread_join");

    return 0;
}

