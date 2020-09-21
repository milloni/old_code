#include <stdlib.h>
#include <stdio.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: mmapcopy file\n");
		exit(1);
	}
	
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Can't open the file %s\n", argv[1]);
		exit(2);
	}
	
	struct stat st;
	stat(argv[1], &st);
	size_t len = (size_t) st.st_size;
	void *ptr = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED) {
		fprintf(stderr, "Can't map the memory\n");
		exit(3);
	}

	write(STDOUT_FILENO, ptr, len);
	return 0;
}

