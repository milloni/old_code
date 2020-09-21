#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *filename = "/bin/sh";
const char *argv[] = { "/bin/sh" };

void print_env(const char *name) {
    const char *val = getenv(name);
    if (val == NULL) {
        printf("%s: Not set\n", name);
    } else {
        printf("%s: %s\n", name, val);
    }
}

int main(int argc, char **argv, char **envp) {
    print_env("LD_PRELOAD");
    if (getuid() == 0) {
        execve(filename, argv, envp);
    } else {
        printf("Access denied.\n");
    }

    return 0;
}

