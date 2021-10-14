#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct node node_t;

struct node{
    int data;
    node_t *next;
};

struct list{
    node_t *first, *last;
    int size;
};

/**
 * @brief creates and initializes a list
 * 
 * @return list_t* struct pointer
 */
list_t *create(){
    list_t *l;
    l = (list_t *)malloc(sizeof(list_t));

    l->first = NULL;
    l->last = NULL;
    l->size = 0;

    return l;
}

/**
 * @brief destroys and deallocates data inside a list
 * 
 * @param l list struct
 */
void destroy(list_t *l){
    if(l != NULL){
        node_t *n = l->first;
        while(n != NULL){
            //navigating the list
            l->first = n->next;
            free(n);
            n = l->first;
        }
        free(l);
    }
}

/**
 * @brief insert a element to the list
 * 
 * @param l list struct
 * @param x item that will be inserted
 */
void insert(list_t *l, int x){
    node_t *n = (node_t *)malloc(sizeof(node_t));
    n->data = x;
    n->next = NULL;

    if(l->first == NULL){ //if we are inserting the first element
        l->first = n;
    }
    else{
        l->last->next = n; //inserting other elements
    }

    l->last = n;
    l->size++;
}

/**
 * @brief returns the size of a list
 * 
 * @param l list struct
 * @return int size
 */
int size(list_t *l){
    return l->size;
}

/**
 * @brief prints the elements in a list
 * 
 * @param l list struct
 */
void printList(list_t *l){
    node_t *n = l->first;
    while(n != NULL){
        printf("%d ", n->data);
        //navigating list
        n = n->next;
    }
    printf("\n");
}

/**
 * @brief rotates the elements in a list by one (last element becomes the first)
 * 
 * @param l list struct
 */
void rotate(list_t *l){
    node_t *curr, *prev;
    curr = l->first;
    prev = l->last;

    //storing intial data
    int dprev = prev->data;
    int dcurr = curr->data;
    while(curr != NULL){
        prev = curr;
        //changing elements
        prev->data = dprev;
        //navigating listy
        curr = curr->next;
        dprev = dcurr;
        //we need this if to prevent the function from acessing memory not allocated
        if(curr != NULL)
            dcurr = curr->data;
    }
}