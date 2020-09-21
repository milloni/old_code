#include <stdio.h>
#include <stdlib.h>

#define M (15)
#define N (4)

void arith(int x, int y) {
	printf("%d %d\n", x * M, y / N);
}

void optarith(int x, int y) {
	int t = x;
	x <<= 4;
	x -= t;
	if (y < 0) y += 3;
	y >>= 2;
	printf("%d %d\n", x, y);
}

int main(void) {
	int x = 0;
	int y = 0;
	scanf("%d %d", &x, &y);
	arith(x, y);
	optarith(x, y);
	return 0;
}

