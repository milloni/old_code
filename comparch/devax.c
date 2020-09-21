#include <stdlib.h>
#include <stdio.h>

int bis(int x, int m) {
	return x | m;
}

int bic(int x, int m) {
	return x & (~m);
}

int main(void) {
	return 0;
}
