#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

enum {
    CMD_UNKNOWN,
    CMD_HELP,
    CMD_QUIT,
    CMD_READ,
};

void err(const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    fprintf(stderr, "[Error] ");
    vfprintf(stderr, msg, args);
    va_end(args);
    perror(msg);
}

void wrn(const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    fprintf(stderr, "[Warning] ");
    vfprintf(stderr, msg, args);
    va_end(args);
    perror(msg);
}

void inf(const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    fprintf(stderr, "[Info] ");
    vfprintf(stderr, msg, args);
    va_end(args);
}

int req_puts(int fd, const char *str)
{
    ssize_t sz = strlen(str);
    const void *read_ptr = str;
    size_t bytes_written = 0;
    size_t bytes_left = sz;
    ssize_t rc;

    printf("SZ: %ld\n", sz);

    while ((rc = write(fd, read_ptr, bytes_left)) != (ssize_t)bytes_left) {
        if (rc < 0) {
            return rc;
        }
        read_ptr += (size_t)rc;
        bytes_written += (size_t)rc;
        bytes_left -= (size_t)rc;
    }
    return 0;
}

int req_gets_until(int fd, char *buf, size_t bufsz, int ch)
{
    char *write_ptr = buf;
    ssize_t rc;

    while (write_ptr < buf + bufsz - 1 && (rc = read(fd, write_ptr, 1) != 0)) {
        if (rc < 0) {
            return rc;
        }
        assert(rc == 1);
        if (*write_ptr == ch) {
            break;
        }
        write_ptr++;
    }
    if (*write_ptr == ch) {
        *write_ptr = '\0';
        return 0;
    }
    *write_ptr = '\0';
    return -1;
}

int parse_command(const char *cmdstr, int *arg)
{
    int arg_cand;
    int rc;
    printf("%s\n", cmdstr);

    if (strncmp(cmdstr, "HELP", 4) == 0) {
        return CMD_HELP;
    } else if (strncmp(cmdstr, "QUIT", 4) == 0) {
        return CMD_QUIT;
    } else if (strncmp(cmdstr, "READ", 4) == 0) {
        rc = sscanf(cmdstr, "READ %d", &arg_cand);
        if (rc == 1) {
            *arg = arg_cand;
            return CMD_READ;
        }
    }
    return CMD_UNKNOWN;
}

#define WISDOM_MAX_NUM 10
#define WISDOM_MAX_SZ 64
#define SOCKBUF_SZ 64
int main(int argc, char **argv)
{
    char wisdom[WISDOM_MAX_SZ][WISDOM_MAX_NUM];
    int passive_sockfd;
    int req_sockfd;
    int rc;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_sz;
    char sockbuf[64];
    int cmd;
    int cmd_arg;
    int running = 1;
    char *wisdom_ptr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }

    memset(wisdom, '\0', sizeof(wisdom));
    memset(sockbuf, '\0', sizeof(sockbuf));
    passive_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (passive_sockfd == -1) {
        perror("Could not create server socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    rc = bind(passive_sockfd, (struct sockaddr *)&server_addr,
        sizeof(server_addr));
    if (rc == -1) {
        perror("Could not bind server socket");
        return 1;
    }
    rc = listen(passive_sockfd, 1024);
    if (rc == -1) {
        perror("Could not mark server socket as passive");
        return 1;
    }

    while (1) {
        client_addr_sz = sizeof(client_addr);
        req_sockfd = accept(passive_sockfd, (struct sockaddr *)&client_addr,
            &client_addr_sz);
        if (req_sockfd == -1) {
            wrn("Could not handle incoming connection");
        }
        inf("Received an incoming connection from %s\n",
            inet_ntoa(client_addr.sin_addr));

        running = 1;
        while (running) {
            req_puts(req_sockfd, "What do you want me to do? (type HELP if stuck)\n");
            req_gets_until(req_sockfd, sockbuf, sizeof(sockbuf), '\n');
            cmd = parse_command(sockbuf, &cmd_arg);
            switch (cmd) {
              case CMD_UNKNOWN:
              case CMD_HELP:
                req_puts(req_sockfd, "Commands: HELP, ADD, READ <index>, QUIT\n");
                break;

              case CMD_QUIT:
                req_puts(req_sockfd, "Bye!\n");
                running = 0;
                break;

              case CMD_READ:
                wisdom_ptr = (void *)wisdom + WISDOM_MAX_SZ * cmd_arg;
                puts(wisdom_ptr);
                req_puts(req_sockfd, "Reading..\n");
                req_puts(req_sockfd, wisdom_ptr);
                break;

              default:
                assert(!"Unknown command");
                break;
            }
        }
        close(req_sockfd);
        req_sockfd = -1;
    }

    printf("Exiting!\n");
    return 0;
}
