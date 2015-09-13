/*mylib.c*/
#include <stdio.h> /* for fprintf */
#include <stdlib.h> /* for size_t, malloc, realloc, exit */
#include "mylib.h"
#include "htable.h"
#include <assert.h>
#include <ctype.h>

/* Allocates size bytes of memory and completes the neccessary checks
@param s - takes a specified size as an argument.
Void function so nothing returned.*/
void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}
/*creates extra memory when required.
@param *p - acts a pointer.
@param s - takes a specified size as an argument.*/
void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if (NULL == result) {
        fprintf(stderr, "memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return result;
}
/*Reads in words one at a time from the file stream and uses isalnum()
to check the character passed is alphanumeric and ensures c isn't
at the end of the file (EOF). 
@param s - the word that is read in from the file. 
@param limit - a count variable to keep track of characters in words.
@param stream - the file that words are read from. 
Returns an integer */ 
int getword(char *s, int limit, FILE *stream) {
    int c;
    char *w = s;
    /* */
    assert(limit > 0 && s != NULL && stream != NULL);
    /* skip to the start of the word.*/
    while (!isalnum(c = getc(stream)) && EOF != c)
        ;
    if (EOF == c) {
        return EOF;
    } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
        *w++ = tolower(c);
    }
    /*alphanumeric check */
    while (--limit > 0) {
        if (isalnum(c = getc(stream))) {
            *w++ = tolower(c);
        } else if ('\'' == c) {
            limit++;
        } else {
            break;
        }
    }
    *w = '\0';
    return w - s;
}

