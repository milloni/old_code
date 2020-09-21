#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
#ifdef _DEFAULT_SOURCE
    printf("_DEFAULT_SOURCE\n");
#endif

    struct in_addr in;
    inet_aton("127.0.0.1", &in);
    printf("%x\n", in.s_addr);
    return 0;
}

