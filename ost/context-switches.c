#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

int prime(int64_t n) {
    if (n < 2) return 0;

    for (int64_t i = 2; i < n; i++) {
        if (n % i == 0) return 0;
    }

    return 1;
}

int main(int argc, char **argv) {
    struct rusage resource_usage;
    pid_t pid;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    int64_t n = atoll(argv[1]);

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        printf("%s\n", prime(n) ? "prime" : "not prime");
        return 0;
    }
    
    if (wait3(NULL, 0, &resource_usage) == -1) {
        perror("wait3");
        return 1;
    }
    long ctx_switches = resource_usage.ru_nvcsw + resource_usage.ru_nivcsw;
    printf("Context switches: %ld\n", ctx_switches);

    return 0;
}

