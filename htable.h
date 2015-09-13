/*htable.c*/
#ifndef HTABLE_H_
#define HTABLE_H_
#include <stdio.h>
#include "container.h"
typedef struct htablerec *htable;
extern void htable_free(htable h);
extern int htable_insert(htable h, char *str);
extern htable htable_new(int capacity, container_t type);
extern void htable_print(htable h);
extern int htable_search(htable h, char *str);

#endif