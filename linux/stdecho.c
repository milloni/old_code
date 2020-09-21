#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
    char c;
    ssize_t ret;
    while ((ret = read(STDIN_FILENO, &c, 1)) != 0) {
        if (ret == -1) {
            if (errno == EINTR) {
                continue;
            } else {
                perror("read");
                printf("An error has occurred\n");
                exit(EXIT_FAILURE);
            }
        }

        ssize_t ret2;
        while ((ret2 = write(STDOUT_FILENO, &c, 1)) != 1) {
            if (ret2 == -1) {
                if (errno == EINTR) {
                    continue;
                } else {
                    perror("write");
                    printf("An error has occurred\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    return 0;
}

