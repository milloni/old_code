#include <stdlib.h>
#include <stdio.h>

void cond(int a, int *p);

int main(void) {
	int d = -1;
	int a = 0;
	scanf("%d", &a);
	cond(a, &d);
	printf("%d\n", d);
	return 0;
}

