#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define UNUSED(x) (void)(x)

static ssize_t _do_read(int fd, char *ptr) {
    static char buf[1024];
    static int idx = 0;
    static int ret = 0;

    if (ret <= 0) {
        while (1) {
            ret = read(fd, buf, 1024);
            if (ret == -1) {
                if (errno == EINTR) continue;
                else return -1;
            } else if (ret == 0) {
                return 0;
            }

            break;
        }

        idx = 0;
    }

    *ptr = buf[idx++];
    ret--;
    return 1;
}

/* Loosely based on getdelim from glibc and readline from
 * "Computer Systems: A Programmer's Perspective"
 * by R. E. Bryant, D. R. O’Hallaron
 * Not thread-safe unlike glibc implementation 
 * VERSION: 0.2 */
ssize_t readuntil(char **lineptr, size_t *n, int delim, int fd) {
    if (lineptr == NULL || n == 0) {
        errno = EINVAL;
        return -1;
    }

    /* The goal is not to do any reallocations in the vast majority of
     * cases, i.e. 1024 should be big enough for most reads. */
    if (*lineptr == NULL || *n == 0) {
        *n = 1024;
        *lineptr = malloc(*n);
        if (*lineptr == NULL) {
            return -1;
        }
    }

    char *ptr = *lineptr;
    char tmp;
    int i;
    for (i = 1; i < (int)*n; i++) {
        ssize_t ret = _do_read(fd, &tmp);
        if (ret == 1) {
            if (tmp == delim) break;
            *ptr++ = tmp;
        } else if (ret == 0) {
            if (i == 1) return 0;
            else break;
        } else {
            return -1;
        }
    }

    *ptr = '\0';
    return i;
}

ssize_t readline(char **lineptr, size_t *n, int fd) {
    return readuntil(lineptr, n, '\n', fd);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: readuntil <file>\n");
        return 1;
    }

    char *fname = argv[1];
    int fd = open(fname, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Can't open the file %s\n", fname);
        perror("open");
        return 1;
    }

    ssize_t ret;
    char *buf = NULL;
    size_t n = 0;

    for (int i = 1; (ret = readline(&buf, &n, fd)) != 0; i++) {
        if (ret == -1) {
            fprintf(stderr, "Error reading the file\n");
            perror("read_until");
            return 1;
        }

        printf("Line %d: %s\n", i, buf);

        free(buf);
        buf = NULL;
        n = 0;
    }

    return 0;
}

