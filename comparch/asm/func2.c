#include <stdlib.h>

int foo(int x, int y) {
	return 0xc0de;
}

int bar(void) {
	foo(0xdead, 0x1337);
	return 0xbeef;
}
