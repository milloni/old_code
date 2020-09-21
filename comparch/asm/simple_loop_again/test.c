#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char c = 0xff;
	unsigned char uc = 0xff;
	int i = c;
	int iu = c;
	printf("%#x\n", c);
	printf("%#x\n", i);
	return 0;
}

