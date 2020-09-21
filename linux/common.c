#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "common.h"

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
 * VERSION: 0.2b */
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
            *ptr++ = tmp;
            if (tmp == delim) break;
        } else if (ret == 0) {
            if (i == 1) return 0;
            else break;
        } else {
            return -1;
        }
    }

    //*ptr = '\0';
    return i;
}

ssize_t readn(int fd, void *buf, size_t count) {
    ssize_t nleft = (ssize_t)count;
    ssize_t nread = 0;
    void *ptr = buf;
    ssize_t ret;
    while (nleft > 0 && (ret = read(fd, ptr, nleft)) != 0) {
        if (ret == -1) {
            if (errno == EINTR) {
                nread = 0;
            } else {
                return -1;
            }
        }

        nread += ret;
        nleft -= ret;
        ptr += ret;
    }

    return nread;
}

ssize_t writen(int fd, const void *buf, size_t count) {
    ssize_t nleft = (ssize_t)count;
    ssize_t nwritten = 0;
    const void *ptr = buf;
    ssize_t ret;
    while (nleft > 0) {
        ret = write(fd, ptr, nleft);
        if (ret == -1) {
            if (errno == EINTR) {
                ret = 0;
            } else {
                return -1;
            }
        }

        nwritten += ret;
        nleft -= ret;
        ptr += ret;
    }

    return nwritten;
}

