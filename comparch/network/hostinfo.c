#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void _f(void) {
    fprintf(stderr, "An error has occurred\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: hostinfo (<domain-name>|<dotted-decimal>)\n");
        exit(EXIT_FAILURE);
    }

    struct hostent *hostinfo = gethostbyname(argv[1]);
    if (hostinfo == NULL) _f();

    printf("official hostname: %s\n", hostinfo->h_name);
    for (char **ptr = hostinfo->h_aliases; *ptr != NULL; ptr++) {
        printf("alias: %s\n", *ptr);
    }
    for (char **ptr = hostinfo->h_addr_list; *ptr != NULL; ptr++) {
        struct in_addr addr;
        addr.s_addr = (uint32_t)*ptr;
        printf("address: %s\n", inet_ntoa(addr));
    }

    return EXIT_SUCCESS;
}

