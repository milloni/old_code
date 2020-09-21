#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#define UNUSED(x) (void)(x)
#define NITERS (1000)

unsigned int cnt = 0;

void *count(void *arg);

void _f(const char *msg) {
    perror(msg);
    exit(1);
}

int main(void) {
    pthread_t tid1, tid2;
    if (pthread_create(&tid1, NULL, count, NULL) != 0) _f("pthread_create");
    if (pthread_create(&tid2, NULL, count, NULL) != 0) _f("pthread_create");
    if (pthread_join(tid1, NULL) != 0) _f("pthread_joint");
    if (pthread_join(tid2, NULL) != 0) _f("pthread_joint");

    if (cnt != ((unsigned)NITERS) * 2) {
        printf("BOOM! cnt=%u\n", cnt);
    } else {
        printf("OK cnt=%u\n", cnt);
    }

    return 0;
}

void *count(void *arg) {
    UNUSED(arg);

    for (int i = 0; i < NITERS; i++) cnt++;
    return NULL;
}

