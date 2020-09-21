#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "header.h"

void structure_copy(Structure *dst, Structure *src) {
	memcpy(dst, src, sizeof(Structure));
}

