#include <stdlib.h>
#include <stdio.h>

#include <dlfcn.h>

#include "vector.h"

#define LIBVECTOR_PATH "./libvector.so"

int x[2] = {1, 2};
int y[2] = {3, 4};
int z[2];

void *my_handle = NULL;
void (*rtl_addvec)(int *x, int *y, int *z, int n) = NULL;

void doom(const char *msg) {
	fprintf(stderr, "%s", msg);
	exit(1);
}

void load_libvector(const char *path) {
	my_handle = dlopen(LIBVECTOR_PATH, RTLD_NOW);
	if (my_handle == NULL) doom("dlopen() error.\n");
	rtl_addvec = dlsym(my_handle, "addvec");
	//printf("%#x\n", (unsigned int)my_handle);
}

void unload_libvector(void) {
	//printf("%#x\n", (unsigned int)handle);
	if (dlclose(my_handle) != 0) {
		// Should I do something?
	}
}

int main(void) {
	load_libvector(LIBVECTOR_PATH);
	//printf("%#x\n", (unsigned int)my_handle);
	if (rtl_addvec == NULL) exit(1);
	rtl_addvec(x, y, z, 2);
	printf("z = [%d, %d]\n", z[0], z[1]);
	unload_libvector();
	return 0;
}

