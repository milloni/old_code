#ifndef _COMMON_H
#define _COMMON_H

#include <unistd.h>

#define UNUSED(x) (void)(x)

/* error-handling wrapper for pthread_create */
extern void pthread_create_w(pthread_t *thread, const pthread_attr_t *attr,
        void *(*start_routine)(void *), void *arg);

/* error-handling wrapper for pthread_join */
extern void pthread_join_w(pthread_t thread, void **retval);

/* error-handling wrapper for pthread_mutex_lock */
extern void pthread_mutex_lock_w(pthread_mutex_t *mutex);

/* error-handling wrapper for pthread_mutex_unlock */
extern void pthread_mutex_unlock_w(pthread_mutex_t *mutex);

/* prints to stderr a message in format "{msg}:{string-from-errnum}\n" 
 * and exits with code 1. */
extern void err2(const char *msg, int errnum);

/* reads from fd to a buffer pointed to by lineptr.
 * if *lineptr is NULL or n points at 0, then a new buffer is allocated 
 * length of this buffer is stored in n. caller is responsible for 
 * releasing this buffer with a call to free() */
extern ssize_t readuntil(char **lineptr, size_t *n, int delim, int fd);

/* reads from fd to buf in a loop until count bytes is read */
extern ssize_t readn(int fd, void *buf, size_t count);

/* writes from buf to fd in a loop until count bytes is written */
extern ssize_t writen(int fd, const void *buf, size_t count);

/* reads a line from fd to a buffer pointed to by lineptr.
 * see readuntil for details. */
static inline ssize_t readline(char **lineptr, size_t *n, int fd) {
    return readuntil(lineptr, n, '\n', fd);
}

union seed_t {
    uint64_t num;
    uint16_t tab[4];
};

/* A class representing a random number generator.
 * State is stored in the object. */
class Rng {
public:
    /* constructor */
    Rng(uint64_t ctrseed);

    /* get next double */
    double next_double(void);

private:
    seed_t seed;
};

#endif /* !_COMMON_H */

