#include <stdio.h>

void f(void);

int x = 15213;
int y = 15212;

int main(void) {
	f();
	printf("x = %#x y = %#x\n", x, y);
	return 0;
}

