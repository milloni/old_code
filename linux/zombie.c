#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    for (int i = 0; i < 100; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Oops\n");
            exit(1);
        } else if (pid == 0) {
            printf("Child pid: %d\n", getpid());
            exit(0);
        }
    }

    return 0;
}

