#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>

void gtfo(int code) {
	fprintf(stderr, "Error: %d\n", code);
	exit(code);
}

void handler(int something) {
	static int beeps = 0;
	
	printf("BEEP\n");
	if (++beeps < 5) {
		alarm(1);
	} else {
		printf("BOOM!\n");
		exit(0);
	}
}

int main(void) {
	if (signal(SIGALRM, handler) == SIG_ERR) gtfo(1);
	alarm(1);
	while (1); // Signal handler returns coontrol here each time.
	return 0;
}

