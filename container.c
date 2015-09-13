/*container.c*/
#include "flexarray.h"
#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "htable.h"
#include "container.h"
#include "rbt.h"
#include <string.h>


struct containerrec {
    container_t type;
    void *contents;
};

/*Establishes what type the container is and calls a specific new() function.
emalloc called to allocate memory relative to the size of the container itself.
Returns the container.*/
container new_container(container_t type){
    container c = emalloc(sizeof *c);
    c->type = type;
    
    if(c->type == RED_BLACK_TREE){
        c->contents = rbt_new();
    }else{
       c->contents = flexarray_new();
    }
    return c;
}

/*Inserts an element into the container by recognising the container type and calling
the specific function for the type. (rbt_insert() OR flexarray_append() )
@param  c - the container which will hold the element
@param *word - points to the word that has been read in and is now being added in the correct position*/
void container_add(container c, char *word) {
    if (c->type == RED_BLACK_TREE) {
        c->contents = rbt_insert(c->contents, word);
    } else {
        flexarray_append(c->contents, word);
    }
}

/*The print function, that individually prints each string.
@param *str - points to the particular element to be printed. */
void print_str(char *str){
    printf(" %s ", str);
}
/* A method which calls the correct search function depending on the type of cotainer.
@param c - the container to be searched.
@param *str - *str, word that is being searched.
Returns 1 if the rbt or flexarray search finds the element and 0 if they do 
not find the element.*/
int container_search(container c, char *str){
    if(c->type == RED_BLACK_TREE){
        return rbt_search(c->contents,str);
    }else{
        return is_present(c->contents, str);
    }
}
/*A method which calls the correct print function depending on the type of the container.
@param c - the container that is holding the elements. This will be either a RBT
or a flexarray.*/
void container_print(container c){
    if(c->type == RED_BLACK_TREE){
        rbt_preorder(c->contents, print_str);
    }else{
        visit(c->contents, print_str);
    }
}

/*Free's the memory that has been allocated from the container
@param- c is the container to be free'd*/
container free_container(container c){
    if(c->type == RED_BLACK_TREE){
        rbt_free(c->contents);
    }else{
        flexarray_free(c->contents);
    }
    free(c);
    
    return NULL;
}



