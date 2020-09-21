#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "common.h"

/* Connects to an echo server (see echo-server-*.c)
 * Usage: echo-client <host> <port> */
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: echo-client <address> <port>\n");
        exit(1);
    }
    char *host = argv[1];
    char *port = argv[2];
    int result = 0;

    struct addrinfo *hostai;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_ADDRCONFIG;
    int ret = getaddrinfo(host, port, &hints, &hostai);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        exit(1);
    }

    int sockfd = socket(hostai->ai_family, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        result = 1;
        goto cleanup_and_exit;
    }

    if (connect(sockfd, hostai->ai_addr, hostai->ai_addrlen) == -1) {
        perror("connect");
        result = 1;
        goto cleanup_and_exit;
    }

    char *str = NULL;
    size_t n = 0;
    ssize_t sz;
    while ((sz = getline(&str, &n, stdin)) != -1) {
        writen(sockfd, str, sz);
        free(str);
        str = NULL;
        n = 0;

        ssize_t sz2 = readline(&str, &n, sockfd);
        writen(STDOUT_FILENO, str, sz2);
        free(str);
        str = NULL;
        n = 0;
    }

cleanup_and_exit:
    close(sockfd);
    freeaddrinfo(hostai);
    return result;
}

