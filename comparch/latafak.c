#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int x = 0x98FDECBA;
	printf("%#010x\n", (~0xFF) | x);
	printf("%#010x\n", (~x & 0xFF) | (x & ~0xFF));
	printf("%#010x\n", x & ~0xFF);
	return 0;
}

