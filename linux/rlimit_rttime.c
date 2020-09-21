#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>

int main(void) {
    struct rlimit rlim;
    rlim.rlim_cur = 16;
    rlim.rlim_max = 16;
    if (setrlimit(RLIMIT_RTTIME, &rlim) == -1) {
        fprintf(stderr, "Oops #1\n");
        return 1;
    }
    if (getrlimit(RLIMIT_RTTIME, &rlim) == -1) {
        fprintf(stderr, "Oops #2\n");
        return 1;
    }
    printf("%lu %lu\n", rlim.rlim_cur, rlim.rlim_max);

    while (1);

    return 0;
}

