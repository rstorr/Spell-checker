/*htable.c*/
#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "htable.h"
#include <string.h>
#include "container.h"

struct htablerec{
    int capacity; 
    container_t type;
    container *containers;
};

/*creates a new htable.
@param capacity - states the amount of space needed.
@param type - determines what container type is used,
either RBT or flexarray.
emalloc used to allocate memory.*/
htable htable_new(int capacity, container_t type){
    int index;
    htable h = emalloc(sizeof * h);
    h->capacity = capacity;
    h->type = type;
    h->containers = emalloc(h->capacity * sizeof h->containers);
    for( index = 0; index < capacity; index++){
        h->containers[index] = NULL;   
    }
    
    return h;
}

/*Free the memory after the program has been executed.
@param h -passes the htable to the method.*/
void htable_free(htable h){
    int i;
    for(i = 0; i < h->capacity; i++){
       if(h->containers[i] != NULL){
            free_container(h->containers[i]);
        }
    }
    free(h->containers);
    free(h);
}

/* Method that converts words to an integer value.
@param *word - points to the word which is being converted.
Returns result, which is the full word converted to integers.*/
 static unsigned int htable_word_to_int(char *word) {
     unsigned int result = 0;
     while (*word != '\0') {
         result = (*word++ + 31 * result);
     }
     return result;
 }

/*Method for inserting elements into the correct position in the hashtable
@param h - the hashtable which the element is being inserted into 
@param *str - the pointer to the word that is being added.
returns an integer to highlight if the word can be successfully inserted or not.*/
 int htable_insert(htable h, char *str){
     unsigned int i = htable_word_to_int(str) % h->capacity;
     if(h->containers[i] == NULL){
         h->containers[i] = emalloc(sizeof h->containers[i]);
         h->containers[i] = new_container(h->type);
     }
    container_add(h->containers[i], str);
    return 1;
 }
 
/* Prints out all the elements in the hashtable.
@param h - the hashtable to be printed
Void function so doesn't return anything.*/
void htable_print(htable h){
    int i = 0;
    for(i = 0;i < h->capacity; i++){
        if(h->containers[i] != NULL){
            printf(" %d-->", i);
            container_print(h->containers[i]);
            printf("\n");
        }
    }
}

/* Used to search either rbt or flex array 
@param h - the hashtable to be searched
@param *str - the word that is being searched for in
the hashtable.
Will return 0 once the method has been executed.
*/
int htable_search(htable h, char *str){
    int index = htable_word_to_int(str) % h->capacity;

    if (h->containers[index] != NULL){
        return container_search(h->containers[index], str);
    }
    
    return 0;
}





   
    
    
