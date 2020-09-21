#include <stdlib.h>
#include <stdio.h>

#include "header.h"

void mat_init(void *mat) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			*((int *)((mat + sizeof(int) * (N * i + j)))) = 0;
		}
	}
}

void mat_increment(int i, int j) {
	int mat[M][N];
	mat_init(mat);
	mat[i][j]++;
	mat_print(mat);
}

