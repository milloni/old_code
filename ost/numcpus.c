#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    long numcores = sysconf(_SC_NPROCESSORS_ONLN);
    if (numcores == -1) {
        perror("sysconf");
        return 1;
    }

    printf("Cores available: %ld\n", numcores);
    return 0;
}

