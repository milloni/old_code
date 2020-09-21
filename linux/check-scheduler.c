#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>

#define POLTR(pol) case pol: return #pol

const char *strpolicy(int policy) {
    switch(policy) {
#ifdef SCHED_OTHER
    POLTR(SCHED_OTHER);
#endif

#ifdef SCHED_BATCH
    POLTR(SCHED_BATCH);
#endif

#ifdef SCHED_IDLE
    POLTR(SCHED_IDLE);
#endif

#ifdef SCHED_FIFO
    POLTR(SCHED_FIFO);
#endif

#ifdef SCHED_RR
    POLTR(SCHED_RR);
#endif

    default: return "unknown";
    }
}

int main(void) {
    struct sched_param param;
    struct timespec ts;
    int policy;
    int max;
    int min;
    double mills;

    memset(&param, 0, sizeof(param));
    memset(&ts, 0, sizeof(ts));
    policy = sched_getscheduler(0);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }
    if (sched_getparam(0, &param) == -1) {
        perror("sched_getparam");
        return 1;
    }
    printf("Scheduling policy: %s\n", strpolicy(policy));
    printf("Static priority: %d\n", param.sched_priority);

    if (sched_rr_get_interval(0, &ts) == -1) {
        perror("sched_rr_get_interval");
        return 1;
    }
    mills = (ts.tv_sec * 1000.0f) + (ts.tv_nsec / 1000000.0f);
    printf("Timeslice in milliseconds for SCHED_RR: %lf\n", mills);

    param.sched_priority = 7;
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler");
        return 1;
    }
    policy = sched_getscheduler(0);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }
    if (sched_getparam(0, &param) == -1) {
        perror("sched_getparam");
        return 1;
    }
    printf("TWEAK\n");
    printf("Scheduling policy: %s\n", strpolicy(policy));
    printf("Static priority: %d\n", param.sched_priority);

    max = sched_get_priority_max(policy);
    if (max == -1) {
        perror("sched_get_priority_max");
        return 1;
    }
    min = sched_get_priority_min(policy);
    if (min == -1) {
        perror("sched_get_priority_min");
        return 1;
    }
    printf("Maximum priority for this scheduling class: %d\n", max);
    printf("Minimum priority for this scheduling class: %d\n", min);

    return 0;
}

