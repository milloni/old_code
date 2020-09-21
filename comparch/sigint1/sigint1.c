#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>

void sigint_handler(int sig) {
	printf("Caught SIGINIT\n");
	exit(0);
}

int main(void) {
	if (signal(SIGINT, sigint_handler) == SIG_ERR) return 1;
	pause(); // Wait for a signal.
	return 0;
}

