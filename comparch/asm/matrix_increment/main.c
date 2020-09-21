#include <stdlib.h>
#include <stdio.h>

#include "header.h"

int main(void) {
	int i = 0;
	int j = 0;
	scanf("%i %i", &i, &j);
	if (i < 0 || i >= M || j < 0 || j >= N) {
		printf("Please don't.\n");
		exit(1);
	}
	mat_increment(i, j);
	return 0;
}

