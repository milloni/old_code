#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

void signal_handler(int signum) {
    if (signum != SIGINT) {
        return;
    }

    printf("SIGINT in process %u\n", getpid());
    exit(1);
}

int main(void) {
    signal(SIGINT, signal_handler);

    printf("Parent:   %u, TTY: %s\n", getpid(), ttyname(STDIN_FILENO));
    for (int i = 0; i < 5; i++) {
        if (fork() == 0) {
            printf("Child #%d: %u, TTY: %s\n", i, getpid(), ttyname(STDIN_FILENO));
            exit(0);
        }
    }

    pid_t pid;
    while ((pid = wait(NULL)) != 0) {
        if (pid == -1 && errno == ECHILD) {
            break;
        }
    }

    return 0;
}

