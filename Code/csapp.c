#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "csapp.h"

/************************** 
 * Error-handling functions
 **************************/
void unix_error(const char *msg) /* unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void posix_error(int code, const char *msg) /* posix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}

void app_error(const char *msg) /* application error */
{
    fprintf(stderr, "%s\n", msg);
    exit(0);
}

/***************************************************
 * Wrappers for dynamic storage allocation functions
 ***************************************************/

void *Malloc(size_t size) 
{
    void *p;

    if ((p  = malloc(size)) == NULL)
	unix_error("Malloc error");
    return p;
}

void *Realloc(void *ptr, size_t size) 
{
    void *p;

    if ((p  = realloc(ptr, size)) == NULL)
	unix_error("Realloc error");
    return p;
}

void *Calloc(size_t nmemb, size_t size) 
{
    void *p;

    if ((p = calloc(nmemb, size)) == NULL)
        unix_error("Calloc error");
    return p;
}

void Free(void *ptr) 
{
    free(ptr);
}

/******************************************
 * Wrappers for the Standard I/O functions.
 ******************************************/
void Fclose(FILE *fp) 
{
    if (fclose(fp) != 0)
        unix_error("Fclose error");
}

FILE *Fdopen(int fd, const char *type) 
{
    FILE *fp;

    if ((fp = fdopen(fd, type)) == NULL)
        unix_error("Fdopen error");

    return fp;
}

char *Fgets(char *ptr, int n, FILE *stream) 
{
    char *rptr;

    if (((rptr = fgets(ptr, n, stream)) == NULL) && ferror(stream))
	app_error("Fgets error");

    return rptr;
}

FILE *Fopen(const char *filename, const char *mode) 
{
    FILE *fp;

    if ((fp = fopen(filename, mode)) == NULL)
	unix_error("Fopen error");

    return fp;
}

void Fputs(const char *ptr, FILE *stream) 
{
    if (fputs(ptr, stream) == EOF)
	unix_error("Fputs error");
}

size_t Fread(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    size_t n;

    if (((n = fread(ptr, size, nmemb, stream)) < nmemb) && ferror(stream)) 
	unix_error("Fread error");
    return n;
}

void Fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    if (fwrite(ptr, size, nmemb, stream) < nmemb)
        unix_error("Fwrite error");
}

void Fseek(FILE *stream, long offset, int whence) {
	int rc = fseek(stream, offset, whence);
	if(rc != 0)
		posix_error(rc, "Fseek error");
}


/* string wrappers */
char *Strdup(const char *s) {
    char *ret = strdup(s);
    if(!ret)
        unix_error("Strdup error");
    return ret;
}
