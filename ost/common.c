#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "common.h"

void err2(const char *msg, int errnum) {
    const int bufsz = 128;
    char buf[bufsz];
    strerror_r(errnum, buf, bufsz);
    fprintf(stderr, "%s: %s\n", msg, buf);
    exit(1);
}

void pthread_create_w(pthread_t *thread, const pthread_attr_t *attr,
        void *(*start_routine)(void *), void *arg)
{
    int ret = pthread_create(thread, attr, start_routine, arg);
    if (ret != 0) {
        err2("pthread_create", ret);
    }
}

void pthread_join_w(pthread_t thread, void **retval) {
    int ret = pthread_join(thread, retval);
    if (ret != 0) {
        err2("pthread_join", ret);
    }
}

void pthread_mutex_lock_w(pthread_mutex_t *mutex) {
    int ret = pthread_mutex_lock(mutex);
    if (ret != 0) {
        err2("pthread_mutex_lock", ret);
    }
}

void pthread_mutex_unlock_w(pthread_mutex_t *mutex) {
    int ret = pthread_mutex_unlock(mutex);
    if (ret != 0) {
        err2("pthread_mutex_unlock", ret);
    }
}

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
        *lineptr = (char *)malloc(*n);
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

