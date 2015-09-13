/*flexarray.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    char **items;
};
/*method that is used to create a new flexarray
returns the result of creating a new flexarray which is empty*/
flexarray flexarray_new() {
    int i;
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
     for(i=0; i < result->capacity; i++){
        result->items[i] = NULL;
    }
    return result;
}
/*Method that is called by container_add to insert an element to the flexarray. 
@param f - the flexarray that the element is being added to.
@param *word - the element being added to the flexarray.*/
void flexarray_append(flexarray f, char *word) {
    if (f->itemcount == f->capacity) {
        f->capacity += f->capacity;
        f->items = erealloc(f->items,f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount] = emalloc((strlen(word)+1)*sizeof (char));
    strcpy(f->items[f->itemcount], word);
    
    f->itemcount++;

}
/*Prints all the elements in the flexarray, is called by container_print().
@param f - the flexarray which is holding the elements to be printed.*/
void flexarray_print(flexarray f) {
    int i;
    for(i = 0; i < f->itemcount; i++){
        printf("%s\n", f->items[i]);
    }
}
/*Free's the flexarray memory that has been allocated.
@param f - the flexarray itself.*/
void flexarray_free(flexarray f) {
    int i = 0;
    for(i = 0; i < f->itemcount; i++){
        free(f->items[i]);
    }
    free(f->items);
    free(f);
}
/*Search function for flexarray and is called from container_search().
@param f - the flexarray to be searched. 
@param *word - the element that is being looked for.
Returns either a 1 or a 0 that corresponds to whether or not the element is present in the flexarray.
1 = element present 0 = element not present.*/
int is_present(flexarray f,char *word){
    int i = 0;
    for(i = 0 ; i < (f-> itemcount) ; i++ ){
        if(strcmp(word, f->items[i])== 0){
            return 1;
        }
    }
    return 0;
}
/*A method which takes a function as a parameter and uses it to print each item in the flexarray. 
@param f - the flexarray that is being printed. 
@param p(char *str) - function that is being used as a parameter.
*/
void visit(flexarray f, void p(char *str)){
    int i = 0;
    for(i =0; i < f->itemcount; i++){
        p(f->items[i]);
}
}
