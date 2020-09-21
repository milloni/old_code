#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp) {
	if (execve("/bin/bash", argv, envp) == -1) return 1;
	return 0;
}

