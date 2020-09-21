#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int x = -1;
	unsigned int ux = (unsigned int)x;
	printf("%u\n", ux);
	printf("%#x\n", ux);
	return 0;
}
