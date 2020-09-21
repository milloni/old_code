#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define SIG (10) // User-defined signal.

static int child_set_up_handler = 0;

void doit_handler(int sth) {
	child_set_up_handler = 1;
}

int gtfo(int code) {
	fprintf(stderr, "Error: %d\n", code);
	exit(code);
}

int main(int argc, char **argv, char **envp) {
	if (signal(SIG, doit_handler) == SIG_ERR) gtfo(5);
	pid_t pid = fork();
	if (pid == -1) gtfo(1);
	if (pid == 0) {
		if (execve("./snooze", argv, envp) == -1) gtfo(2);
	}
	
	while (!child_set_up_handler);
	sleep(50);
	if (kill(pid, SIG) == -1) gtfo(3);
	if (waitpid(pid, NULL, 0) == -1) gtfo(4);
	
	return 0;
}

