#include <stdlib.h>

int f(void) {
	int t1 = 1;
	int t2 = 2;
	int t3 = t1 + t2;
	return f();
}

int main(void) {
	return f();
}

