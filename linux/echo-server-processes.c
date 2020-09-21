#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include "common.h"

int g_servfd;

void signal_handler(int signum) {
    int running = 1;

    switch (signum) {
    case SIGINT:
    case SIGTERM:
        running = 0;

    case SIGCHLD: {
        int status;
        pid_t pid;
        while ((pid = waitpid(-1, &status, WNOHANG)) != 0) {
            if (pid == -1) {
                if (errno == EINTR) continue;
                else if (errno == ECHILD) break;
                else perror("waitpid");
            }

            if (WIFEXITED(status)) {
                fprintf(stderr,
                        "[Info] Worker process %u terminated normally\n",
                        pid);
            } else {
                fprintf(stderr,
                        "[Info] Workder process %u terminated abnormally\n",
                        pid);
            }
        }

        if (!running) {
            fprintf(stderr, "[Info] Shutting down the server process %u\n", getpid());
            close(g_servfd);
            exit(0);
        }
        break;
    }

    default:
        fprintf(stderr, "[Warn] Unexpected signal\n");
        break;
    }
}

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
    signal(SIGCHLD, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    if (argc != 2) {
        fprintf(stderr, "Usage: echo-server <port>\n");
        exit(1);
    }
    int result = 0;
    in_port_t port = atoi(argv[1]);

    g_servfd = socket(AF_INET, SOCK_STREAM, 0);
    if (g_servfd == -1) {
        perror("socket");
        exit(1);
    }

    struct in_addr in_addr;
    in_addr.s_addr = htonl(INADDR_ANY);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr = in_addr;
    if (bind(g_servfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        result = 1;
        goto cleanup_and_exit;
    }
    if (listen(g_servfd, 1024) == -1) {
        perror("listen");
        result = 1;
        goto cleanup_and_exit;
    }

    while (1) {
        struct sockaddr clientaddr;
        struct sockaddr_in *in_clientaddrp = (struct sockaddr_in *)&clientaddr;
        unsigned int socklen = sizeof(clientaddr);
        int connfd = accept(g_servfd, &clientaddr, &socklen);
        if (connfd == -1) {
            perror("connfd");
            fprintf(stderr,
                    "[Warn] Establishing connection with client failed\n");
            continue;
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            fprintf(stderr, "[Warn] Failed to fork a worker process for %s\n",
                    inet_ntoa(in_clientaddrp->sin_addr));
            close(connfd);
            continue;
        } else if (pid == 0) {
            signal(SIGINT, SIG_IGN);
            close(STDIN_FILENO);
            close(g_servfd);
            
            run_worker(connfd, clientaddr);
            return 0;
        }

        close(connfd);
    }

cleanup_and_exit:
    close(g_servfd);
    return result;
}

