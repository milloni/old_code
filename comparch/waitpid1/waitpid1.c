#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N (5)

void gtfo(int code, char *msg) {
	fprintf(stderr, "%s", msg);
	exit(code);
}

int main(void) {
	pid_t pid;
	for (int i = 0; i < N; i++) {
		if ((pid = fork()) == -1) gtfo(1, "Error: fork()\n");
		else if (pid == 0) exit(100 + i);
	}

	int status = 0;
	while ((pid = wait(&status)) > 0) {
		if (WIFEXITED(status)) {
			printf("Child %d terminated normally with exit status=%d\n",
				pid, WEXITSTATUS(status));
		} else {
			printf("Child %d terminated abnormally\n", pid);
		}
	}
	return 0;
}

