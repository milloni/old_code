#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include "common.h"

void display_conninfo(const struct sockaddr_in *addr) {
    char *clientaddr = inet_ntoa(addr->sin_addr);
    fprintf(stderr, "[Info] Received connection from %s\n", clientaddr);
}

void run_worker(int connfd, struct sockaddr clientsockaddr) {
    display_conninfo((struct sockaddr_in *)&clientsockaddr);

    char *buf = NULL;
    size_t n = 0;
    ssize_t sz;
    while ((sz = readline(&buf, &n, connfd)) != 0) {
        writen(connfd, buf, sz);
        free(buf);
        buf = NULL;
        n = 0;
    }
}

/* Listens on a tcp port given on the commandline, echoes input to the
 * connected user, line by line. */
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: echo-server <port>\n");
        exit(1);
    }
    int result = 0;
    in_port_t port = atoi(argv[1]);

    int servfd = socket(AF_INET, SOCK_STREAM, 0);
    if (servfd == -1) {
        perror("socket");
        exit(1);
    }

    struct in_addr inaddr;
    inaddr.s_addr = htonl(INADDR_ANY);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr = inaddr;
    if (bind(servfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        result = 1;
        goto cleanup_and_exit;
    }
    if (listen(servfd, 1024) == -1) {
        perror("listen");
        result = 1;
        goto cleanup_and_exit;
    }

    while (1) {
        struct sockaddr clientaddr;
        size_t socklen = sizeof(clientaddr);
        int connfd = accept(servfd, &clientaddr, &socklen);
        if (connfd == -1) {
            perror("connfd");
            result = 1;
            goto cleanup_and_exit;
        }

        run_worker(connfd, clientaddr);
        close(connfd);
    }

cleanup_and_exit:
    close(servfd);
    return result;
}

