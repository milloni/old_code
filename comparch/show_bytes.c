//
// Little endian or big endian?
//

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void show_bytes(unsigned char *tab, int len) {
	for (int i = 0; i < len; i++) {
		printf("%2x ", tab[i]);
	}
	printf("\n");
}

int main(void) {
	uint32_t i32 = 0xaabbccdd;
	uint64_t i64 = 0xaabbccdd11223344;
	show_bytes((unsigned char *) &i32, sizeof(i32));
	show_bytes((unsigned char *) &i64, sizeof(i64));
	
	return 0;
}

