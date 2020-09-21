#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

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

size_t fsize(FILE *fp) {
    size_t result;
    long old = ftell(fp);
    if (old == EOF) {
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    result = (size_t)ftell(fp);
    if (result == (size_t)EOF) {
        return 0;
    }
    fseek(fp, old, SEEK_SET);
    return result;
}

int main(int argc, char **argv) {
    int pipefd[2];
    int readfd;
    int writefd;
    FILE *srcfp;
    char *src;
    char *dst;
    pid_t pid;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    src = argv[1];
    dst = argv[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
    readfd = pipefd[0];
    writefd = pipefd[1];

    srcfp = fopen(src, "rb");
    if (srcfp == NULL) {
        perror("fopen");
        return 1;
    }
    size_t srcsz = fsize(srcfp);
    if (srcsz == 0) {
        fprintf(stderr, "File is empty\n");
        return 1;
    }
    char *srcbuf = malloc(srcsz);
    if (srcbuf == NULL) {
        perror("malloc");
        return 1;
    }
    if (fread(srcbuf, 1, srcsz, srcfp) != srcsz) {
        perror("fread");
        return 1;
    }
    fclose(srcfp);
    if (writen(writefd, srcbuf, srcsz) == -1) {
        perror("writen");
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    
    if (pid > 0) {
        close(readfd);
        close(writefd);
        wait(NULL);
        return 0;
    }

    close(writefd);
    char *dstbuf = malloc(srcsz);
    if (dstbuf == NULL) {
        perror("malloc");
        return 1;
    }
    if (readn(readfd, dstbuf, srcsz) == -1) {
        perror("read");
        return 1;
    }
    close(readfd);

    FILE *dstfp = fopen(dst, "w");
    if (dstfp == NULL) {
        perror("fopen");
        return 1;
    }

    if (fwrite(dstbuf, 1, srcsz, dstfp) != srcsz) {
        perror("fwrite");
        return 1;
    }
    fclose(dstfp);

    return 0;
}

