#include <stdio.h>

// non-zero if x > y, zero otherwise
int is_greater(int x, int y);

int main(void) {
	int x = 0;
	int y = 0;
	scanf("%d %d", &x, &y);
	if (is_greater(x, y)) {
		printf("%d is greater than %d\n", x, y);
	} else {
		printf("%d is NOT greater than %d\n", x, y);
	}
	return 0;
}

