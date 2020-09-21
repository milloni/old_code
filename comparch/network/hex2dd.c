#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: hex2dd <hex>\n");
        exit(1);
    }

    printf("%s\n", argv[1]);
    uint32_t nip = htonl(strtoul(argv[1], NULL, 16));
    struct in_addr ip;
    ip.s_addr = nip;
    char *sip = inet_ntoa(ip);
    printf("%s\n", sip);

    return 0;
}

