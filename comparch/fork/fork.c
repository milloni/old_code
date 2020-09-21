#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
	int x = 0;
	pid_t pid = fork();
	if (pid == -1) {
		fprintf(stderr, "Error.\n");
		exit(1);
	}
	
	if (pid == 0) {
		printf("Child: %d\n", ++x);
	} else {
		printf("Parent: %d\n", --x);
	}

	return 0;
}

