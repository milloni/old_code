#include <stdlib.h>
#include <stdio.h>

void inplace_swap(int *a, int *b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int main(void) {
	int a = 0;
	int b = 0;
	scanf("%d %d", &a, &b);
	inplace_swap(&a, &b);
	printf("%d %d\n", a, b);
	
	return 0;
}


