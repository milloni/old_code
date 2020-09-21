#include <stdlib.h>
#include <stdio.h>

void array_sum(void) {
	int tab[5];
	for (int i = 0; i < 5; i++) {
		scanf("%d", &tab[i]);
	}
	int sum = 0;
	for (int i = 0; i < 5; i++) {
		sum += tab[i];
	}
	printf("%d\n", sum);
}

