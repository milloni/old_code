#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		return 1;
	}
	
	int64_t i = 0;
	sscanf(argv[1], "%lli", &i);
	int32_t j = (int32_t) i;
	
	printf("%d\n", j);
	return 0;
}

