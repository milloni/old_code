#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N (3)
#define MAXLINE (0x400)

void fatal_error() {
	fprintf(stderr, strerror(errno));
	exit(1);
}

void sigchld_handler(int sig) {
	pid_t pid;
	while ((pid = waitpid(-1, NULL, 0)) > 0) {
		printf("Handler reaped child %d\n", pid);
	}
	if (errno != ECHILD) fatal_error();
	sleep(2);
}

int main(void) {
	if (signal(SIGCHLD, sigchld_handler) == SIG_ERR) fatal_error();
	for (int i = 0; i < N; i++) {
		pid_t pid = fork();
		if (pid == -1) fatal_error();
		if (pid == 0) {
			printf("Hello from child %d\n", (int)getpid());
			sleep(1);
			exit(0);
		}
	}

	char buf[MAXLINE];
	if (fread(buf, 1, MAXLINE, stdin) == 0 && ferror(stdin)) fatal_error();
	
	printf("Parent processing input...\n");
	while (1);

	return 0;
}

