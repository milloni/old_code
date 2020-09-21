#include <stdlib.h>
#include <stdio.h>

int main(void) {
	for (int i = '0'; i <= '9'; i++) {
		printf("%c %2d %#2x\n", i, (int) i, (int) i);
	}
	return 0;
}

