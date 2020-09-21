#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <cstring>
#include <cerrno>

#include "common.h"

using namespace std;

vector<int> g_data;
pthread_mutex_t g_data_mtx = PTHREAD_MUTEX_INITIALIZER;

void err2(const char *msg, int errnum) {
    constexpr int bufsz = 128;
    char buf[bufsz];
    strerror_r(errnum, buf, bufsz);
    fprintf(stderr, "%s: %s\n", msg, buf);
    exit(1);
}

void pthread_create_w(pthread_t *thread, const pthread_attr_t *attr,
        void *(*start_routine)(void *), void *arg)
{
    int ret = pthread_create(thread, attr, start_routine, arg);
    if (ret != 0) {
        err2("pthread_create", ret);
    }
}

void pthread_mutex_lock_w(pthread_mutex_t *mutex) {
    int ret = pthread_mutex_lock(mutex);
    if (ret != 0) {
        err2("pthread_mutex_lock", ret);
    }
}

void pthread_mutex_unlock_w(pthread_mutex_t *mutex) {
    int ret = pthread_mutex_unlock(mutex);
    if (ret != 0) {
        err2("pthread_mutex_unlock", ret);
    }
}

void *run_avg(void *arg) {
    UNUSED(arg);

    static float result = 0;
    for (int i = 0; i < (int)g_data.size(); i++) {
        pthread_mutex_lock_w(&g_data_mtx);
        result += (float)g_data[i] / g_data.size();
        pthread_mutex_unlock_w(&g_data_mtx);
    }

    pthread_exit(&result);
}

void *run_min(void *arg) {
    UNUSED(arg);

    int result = g_data[0];
    for (int i = 1; i < (int)g_data.size(); i++) {
        pthread_mutex_lock_w(&g_data_mtx);
        if (g_data[i] < result) result = g_data[i];
        pthread_mutex_unlock_w(&g_data_mtx);
    }

    pthread_exit((void *)result);
}

void *run_max(void *arg) {
    UNUSED(arg);

    int result = g_data[0];
    for (int i = 1; i < (int)g_data.size(); i++) {
        pthread_mutex_lock_w(&g_data_mtx);
        if (g_data[i] > result) result = g_data[i];
        pthread_mutex_unlock_w(&g_data_mtx);
    }

    pthread_exit((void *)result);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <a0> <a1> ... <an>\n", argv[0]);
        return 1;
    }

    size_t sz = argc - 1;
    g_data.resize(sz);
    for (int i = 0; i < (int)g_data.size(); i++) {
        g_data[i] = atoi(argv[i + 1]);
    }

    pthread_t tid_avg, tid_min, tid_max;
    pthread_create_w(&tid_avg, NULL, run_avg, NULL);
    pthread_create_w(&tid_min, NULL, run_min, NULL);
    pthread_create_w(&tid_max, NULL, run_max, NULL);

    float *avgp;
    float avg;
    int min, max;
    pthread_join(tid_avg, (void **)&avgp);
    avg = *avgp;
    pthread_join(tid_min, (void **)&min);
    pthread_join(tid_max, (void **)&max);
    printf("The average value is %.4f\n", avg);
    printf("The minimum value is %d\n", min);
    printf("The maximum value is %d\n", max);

    return 0;
}

