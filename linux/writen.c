#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>

#define RANDOM_DEVICE "/dev/urandom"

size_t parse_count(const char *s) {
    size_t sz = strlen(s) + 1;
    char *_s = malloc(sizeof(char) * sz);
    if (_s == NULL) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    strncpy(_s, s, sz);

    size_t multiplier = 1;
    switch (_s[sz - 2]) {
    case 'K': multiplier = 1024;               break;
    case 'M': multiplier = 1024 * 1024;        break;
    case 'G': multiplier = 1024 * 1024 * 1024; break;
    default:                                   break;
    }

    if (multiplier != 1) {
        _s[sz - 2] = '\0';
    }
    size_t result = (size_t)strtoul(s, NULL, 10);
    if (result == ULONG_MAX) {
        fprintf(stderr, "Error: count value is invalid\n");
        exit(EXIT_FAILURE);
    }
    result *= multiplier;

    free(_s);
    return result;
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

void fill_random(void *buf, size_t count) {
    int fd = open(RANDOM_DEVICE, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error: can't open the file %s\n", RANDOM_DEVICE);
        exit(EXIT_FAILURE);
    }

    readn(fd, buf, count);
    close(fd);
}

ssize_t writen(int fd, const void *buf, size_t count) {
    ssize_t nleft = (ssize_t)count;
    ssize_t nwritten = 0;
    ssize_t ret;
    while (nleft > 0 && (ret = write(fd, buf, count)) != 0) {
        if (ret == -1) {
            if (errno == EINTR) {
                nwritten = 0;
            } else {
                return -1;
            }
        }

        nwritten += ret;
        nleft -= ret;
    }

    return nwritten;
}

/* Write a buffer of argv[2] random bytes to file argv[1] */
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: writen <file> <count>\n");
        exit(EXIT_FAILURE);
    }

    char *fname = argv[1];
    size_t count = parse_count(argv[2]);

    void *buf = malloc(count);
    if (buf == NULL) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    fill_random(buf, count);

    int fd = open(fname, O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "Error: can't open the file %s\n", fname);
        exit(EXIT_FAILURE);
    }

    writen(fd, buf, count);
    close(fd);

    return EXIT_SUCCESS;
}

