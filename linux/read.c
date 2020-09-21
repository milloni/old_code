#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) return 1;

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) return 1;

    char buf[1024] = { 0 };
    ssize_t ret = read(fd, buf, 1024);
    printf("%d\n", ret);

    return 0;
}

