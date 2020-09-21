#define N (16)
typedef int fix_matrix[N][N]

void fix_set_diag(fix_matrix A, int val) {
	int i = 15;
	int *ptr = A + 255;
	do {
		*ptr = val;
		ptr -= 17;
		i--;
	} while (i >= 0);
}

