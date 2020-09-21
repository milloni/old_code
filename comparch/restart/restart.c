#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

sigjmp_buf buf;

__sighandler_t *Signal(int signum, __sighandler_t *handler) {
	struct sigaction action, old_action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	if (sigaction(signum, &action, &old_action) < 0) {
		exit(1);
	}
	return old_action.sa_handler;
}

void handler(int sig) {
	siglongjmp(buf, 1);
}

int main(void) {
	Signal(SIGINT, handler);
	if (!sigsetjmp(buf, 1)) {
		printf("Starting\n");
	} else {
		printf("Restarting\n");
	}

	while (1) {
		sleep(1);
		printf("Processing...\n");
	}
	return 0;
}

