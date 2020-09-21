#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        fprintf(stderr, "Error");
        return 1;
    }

    if (close(sockfd) == -1) {
        perror("sockfd");
        return 2;
    }
    return 0;
}

