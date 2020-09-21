#include <stdlib.h>
#include <stdio.h>

int fib_dw(int n);

int main(void) {
	int i = 0;
	scanf("%d", &i);
	if (i >= 0) {
		printf("%d\n", fib_dw(i));
	}
	return 0;
}

