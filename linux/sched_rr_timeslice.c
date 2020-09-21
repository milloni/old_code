#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>

int main(void) {
    struct timespec timeslice;

    memset(&timeslice, 0, sizeof(timeslice));
    if (sched_rr_get_interval(0, &timeslice) == -1) {
        perror("sched_rr_get_interval");
        return 1;
    }

    printf("%ld %ld\n", timeslice.tv_sec, timeslice.tv_nsec);

    return 0;
}

