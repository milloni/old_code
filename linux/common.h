#ifndef _COMMON_H
#define _COMMON_H

#define UNUSED(x) (void)(x)

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

#endif /* !_COMMON_H */

