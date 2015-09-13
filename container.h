/*container.h*/
#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <stdio.h>


typedef struct containerrec *container;
typedef enum container_e {FLEX_ARRAY, RED_BLACK_TREE} container_t;
extern void container_add(container c, char *word);
extern void container_print(container c);
extern void print_str(char *str);
extern int container_search(container c, char *str);
extern container new_container();
extern container free_container(container c);
#endif