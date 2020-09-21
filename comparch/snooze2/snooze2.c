#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <signal.h>

void sigint_handler(int sig) {
	// Do nothing.
}

int snooze(int secs) {
	int t = sleep(secs);
	if (t == 0) return secs;
	else return secs - t;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: ./snooze2 secs\n");
		exit(0);
	}

	if (signal(SIGINT, sigint_handler) == SIG_ERR) {
		exit(1);
	}

	int secs = atoi(argv[1]);
	int t = snooze(secs);
	printf("Slept for %d of %d secs.\n", t, secs);
	return 0;
}
