#include <stdlib.h>
#include <stdio.h>

#include "header.h"

void mat_print(void *mat) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			int a = *((int *)(mat + sizeof(int) * (N * i + j)));
			printf("%d ", a);
		}
		printf("\n");
	}
}

