#include <stdlib.h>
#include <stdio.h>

#include "header.h"

void structure_init(Structure *s) {
	if (s == NULL) return;
	s->x = 128;
	s->y = 256;
	s->z = 3.14;
	s->tab[0] = 0;
	s->tab[1] = 1;
	s->tab[2] = 2;
	s->tab[3] = 3;
}

void structure_print(Structure *s) {
	printf("%d\n", s->x);
	printf("%d\n", s->y);
	printf("%f\n", s->z);
	printf("%d %d %d %d\n", s->tab[0], s->tab[1], s->tab[2], s->tab[3]);
}

int main(void) {
	Structure src;
	Structure dst;
	structure_init(&src);
	structure_copy(&dst, &src);
	structure_print(&src);
	puts("----------------------------------------");
	structure_print(&dst);
	return 0;
}

