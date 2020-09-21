#include <stdlib.h>
#include <stdio.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: jello file\n");
		exit(1);
	}

	struct stat st;
	if (stat(argv[1], &st) == -1) {
		fprintf(stderr, "Error: can't locate the file \"%s\"\n", argv[1]);
		exit(2);
	}
	size_t len = (size_t) st.st_size;

	int fd = open(argv[1], O_RDWR);
	if (fd == -1) {
		fprintf(stderr, "Error: can't open the file \"%s\"\n", argv[1]);
		exit(3);
	}

	char *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if ((void *)ptr == MAP_FAILED) {
		fprintf(stderr, "Error: can't map the memory\n)");
		exit(4);
	}
	ptr[0] = 'J';
	
	if (munmap(ptr, len) == -1) {
		fprintf(stderr, "Error: can't unmap the memory\n");
	}
	if (close(fd) == -1) {
		fprintf(stderr, "Error: can't close the file \"%s\"\n", argv[1]);
	}

	return 0;
}

