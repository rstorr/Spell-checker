#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "rbt.h"
#include <string.h>
#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

struct rbt_node {
    char *key;
    rbt_colour colour;
    rbt left;
    rbt right;
};

/*Method that deletes a specified node. Is called by rbt_delete()
@param- b being the tree to be deleted from
Will return the RBT with the node removed.*/
rbt delete_node (rbt b) {
    if(b->right == NULL && b->left ==NULL){
        free(b->key);
        
        b= NULL;
        return b; 
    }else if(b->right !=NULL){
        char *tmp = b->key;
        b->key = b->right->key;
        b->right->key = tmp;
        b = rbt_delete(b,tmp);
    }else if(b->left !=NULL){
        char *tmp = b->key;
        b->key = b->left->key;
        b->left->key = tmp;
        b = rbt_delete(b,tmp);
    }else if(b->left != NULL && b->right !=NULL){

        rbt temp = b->right;
        while(temp ->left != NULL){
            temp = temp->left;

        }
        strcpy(b->key,temp->key);
        b->right=rbt_delete(b->right,temp->key);
        

    }
    return b;
}

/*used to delete from a RBT. Contains all conditionals
that would influence colouration of RBT.
@param - b is the RBT to be deleted from
@param - str is the str to be deleted
returns the RBT after deletion*/
rbt rbt_delete(rbt b, char *str){

    if (NULL == b){
        return b;
    }
    if(strcmp(b->key,str) == 0){
        b =delete_node(b);
    }else if(strcmp(b->key,str) < 0){
        b->right = rbt_delete(b->right, str);
    }else{
        b->left = rbt_delete(b->left,str);
    }
    return b;
}
         


/*Frees the memory that has been allocated 
@param b - the RBT itself.*/
void rbt_free(rbt b){
    if (b != NULL){
        rbt_free(b->left);
        rbt_free(b->right);
        free(b->key);
        free(b);
    }
}

/*A function that is called in rbt_fix() when the rbt needs to be rotated right in order
to conserve/correct rbt properties.
@param r - the red black tree that is being rotated right.
Returns the rotated RBT*/
static rbt right_rotate(rbt r){
    rbt temp;
    temp = r;
    r = temp->left;
  
    temp->left = r->right;
    r->right = temp;
    return r;
}
/*A function that is called in rbt_fix when the rbt needs to be rotated left in order
to conserve/correct rbt properties.
@param r - the red black tree that is being rotated left. 
Returns the rotated RBT*/
static rbt left_rotate(rbt r){
    rbt temp;
    temp = r;
    r = temp->right;
 
    temp->right = r->left;
    r->left = temp;
    return r;
}
/*A method which ensures all the properties of RBT's are conserved. If any deviations are found, 
a colour change is made.
@param r - the container which is of type rbt.
Returns the RBT that has had neccesary changes made to ensure
correct properties.*/
static rbt rbt_fix(rbt r){
    if(IS_RED(r->left) && IS_RED(r->left->left)){
        if(IS_RED(r->right)){
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else {
            r = right_rotate(r);
            r->colour = BLACK;
            r->right->colour = RED;
        }
    }
    else if(IS_RED(r->left) && IS_RED(r->left->right)){
        if(IS_RED(r->right)){
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else {
            r->left = left_rotate(r->left);
            r = right_rotate(r);
            r->colour = BLACK;
            r->right->colour = RED;
        }
    }
    else if(IS_RED(r->right) && IS_RED(r->right->left)){
        if(IS_RED(r->left)){
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else {
            r->right = right_rotate(r->right);
            r = left_rotate(r);
            r->colour = BLACK;
            r->left->colour = RED;
        }
    }
    else if(IS_RED(r->right) && IS_RED(r->right->right)){
        if(IS_RED(r->left)){
            r->colour = RED;
            r->right->colour = BLACK;
            r->left->colour = BLACK;
        } else {
            r = left_rotate(r);
            r->colour = BLACK;
            r->left->colour = RED;
        }
    }
    return r;
}
/*The method which adds elements to the rbt. Is called by the container_add() method.
@param b - the rbt that the element is being added to. 
@ param - *str, the element to be added.*/
        rbt rbt_insert(rbt b, char *str){
    
            if(b == NULL){
                b = emalloc(sizeof *b);
                b->colour = RED;
                b->left = NULL;
                b->right = NULL;
                b->key = emalloc((strlen(str)+1)*sizeof (char));
                strcpy(b->key, str);
            }else if(strcmp(str, b->key) <= 0){
                b->left = rbt_insert(b->left, str);
            }else if(strcmp(str, b->key) > 0){
                b->right = rbt_insert(b->right, str);
            }
            b = rbt_fix(b);
            return b;
        }
        /*just making new NULL space*/
        rbt rbt_new(){
            return NULL;
        }
/*Method prints RBT out into pre-order form
@param- b is the RBT
@param- f is a function parameter that will be used to print the RBT*/
void rbt_preorder(rbt b, void f (char *str)){

            if(NULL == b){
                return;
            }

            f(b->key);
            rbt_preorder(b->left, f);
            rbt_preorder(b->right,f);

        }
/*Method prints RBT out into inorder-order form
@param- b is the RBT
@param- f is a function parameter that will be used to print the RBT*/
void rbt_inorder(rbt b, void f (char *str)){
    if(NULL == b){
        return;
    }
    
    rbt_inorder(b->left, f);
    f(b->key);
    rbt_inorder(b->right,f); 

}
/*Search function for RBT and is called from container_search. 
@param b - the rbt tp be searced.
@param *str - the element which is being looked for.
returns either a 1 or a 0 that corresponds to whether or not the element 
is present in the flexarray. 1 = element present 0 = element not present.*/
int rbt_search(rbt b, char *str){
    if(b==NULL){
        return 0;
    }
    
    if(strcmp(str, b->key)==0){
        return 1;
        
    }else if(strcmp(str, b->key)<=0){
        return rbt_search(b->left, str);
    
    } else if(strcmp(str, b->key)>=0){
        return rbt_search(b->right, str);
    }
    
    return 0;
    
}


