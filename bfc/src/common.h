#ifndef _COMMON_H
#define _COMMON_H

#include <stdlib.h>

#define BFC_COD_BUFSIZE (1024 * 1024)

void bfc_fatal(const char *s);
void bfc_warn(const char *s);
void _d_perror(const char *s);
size_t file_size(int fd);
long read_all(int fd, char *buf, size_t count);
char *bfc_load_bfcode(const char *path);
void bfc_free_code_buf(void *buf);
void bfc_verify_code(const char *code);

#endif // _COMMON_H

