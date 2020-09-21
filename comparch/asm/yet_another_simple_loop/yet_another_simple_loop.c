#include <stdio.h>
#include <stdlib.h>

void yet_another_simple_loop(void) {
	for (int i = 0; i < 0x10; i++) {
		printf("Loop count: %#x\n", i);
	}
}

