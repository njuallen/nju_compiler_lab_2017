#ifndef __CSAPP_H__
#define __CSAPP_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include "linkage.h"

/* Our own error-handling functions */
LINKAGE void unix_error(const char *msg);
LINKAGE void posix_error(int code, const char *msg);
LINKAGE void app_error(const char *msg);

/* Standard I/O wrappers */
LINKAGE void Fclose(FILE *fp);
LINKAGE FILE *Fdopen(int fd, const char *type);
LINKAGE char *Fgets(char *ptr, int n, FILE *stream);
LINKAGE FILE *Fopen(const char *filename, const char *mode);
LINKAGE void Fputs(const char *ptr, FILE *stream);
LINKAGE size_t Fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
LINKAGE void Fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
LINKAGE void Fseek(FILE *stream, long offset, int whence);

/* Dynamic storage allocation wrappers */
LINKAGE void *Malloc(size_t size);
LINKAGE void *Realloc(void *ptr, size_t size);
LINKAGE void *Calloc(size_t nmemb, size_t size);
LINKAGE void Free(void *ptr);

/* string wrappers */
LINKAGE char *Strdup(const char *s);
LINKAGE char *Asprintf(const char *fmt, ...);
#endif
