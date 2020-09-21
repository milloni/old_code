#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define SHMSZ 4096
#define SHMNAME "/collatz_shm"

int shmfd;
void *shmptr;

int collatz(int n) {
    if (n % 2 == 0) {
        return n / 2;
    } else {
        return 3 * n + 1;
    }
}

void run_child(int n) {
    int *buf = (int *)shmptr;

    int i = 0;
    while (n > 1) {
        buf[i] = n;
        n = collatz(n);
        i++;
    }
    buf[i] = n;

    munmap(shmptr, SHMSZ);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "n must be > 0\n");
        return 1;
    }

    shmfd = shm_open(SHMNAME, O_CREAT | O_RDWR, 0666);
    if (shmfd == -1) {
        perror("shm_open");
        return 1;
    }
    if (ftruncate(shmfd, SHMSZ) == -1) {
        perror("ftruncate");
        return 1;
    }
    shmptr = mmap(NULL, SHMSZ, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if (shmptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        run_child(n);
        return 0;
    } else {
        wait(NULL);
        int *buf = (int *)shmptr;
        int i = 0;
        for (i = 0; buf[i + 1] != 0; i++) {
            printf("%d ", buf[i]);
        }
        printf("%d\n", buf[i]);

        munmap(shmptr, SHMSZ);
        shm_unlink(SHMNAME);
        return 0;
    }

    /* NOTREACHED */
    return 0;
}

