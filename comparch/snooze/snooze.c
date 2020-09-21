#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define SIG (10) // User-defined signal.

void snooze_handler(int sth) {
	printf("Handler called\n");
	// Do nothing from something.
}

unsigned int snooze(unsigned int secs) {
	unsigned t = sleep(secs);
	if (t == 0) t = secs;
	else t = secs - t;
	return t;
}

int main(void) {
	while (signal(SIG, snooze_handler) == SIG_ERR);
	pid_t parent = getppid();
	while (kill(parent, SIG) == -1);
	printf("%d\n", snooze(100));
	return 0;
}

