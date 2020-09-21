#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: dd2hex <ip>\n");
        exit(1);
    }

    char *ip = argv[1];
    struct in_addr in;
    if (inet_aton(ip, &in) != 1) {
        fprintf(stderr, "Could not interpret the argument\n");
        exit(1);
    }
    uint32_t result = ntohl(in.s_addr);
    printf("%x\n", result);

    return 0;
}

