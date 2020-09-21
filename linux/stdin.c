#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFSIZE (1024)

long read_all(int fd, char *buf, size_t count) {
    int bytes_read = 0;
    char *_buf = (char *) buf;
    ssize_t ret;
    while (count > 0 && (ret = read(fd, _buf, count)) != 0) {
        if (ret == -1) {
            if (errno == EINTR) continue;
            return -1;
        }

        bytes_read += ret;
        count -= ret;
        _buf += ret;
    }

    return bytes_read;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    char *buf = malloc(BUFSIZE);
    if (buf == NULL) return 1;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) return 1;
    int ret = read_all(fd, buf, BUFSIZE);
    write(STDOUT_FILENO, buf, ret);
    close(fd);
    return 0;
}

