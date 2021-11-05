#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

typedef struct node node_t;
struct node{
    void *data;
    node_t *next;
};

struct list{
    node_t *head, *tail;
    int size;
    void (*free) (void *);
    void (*print) ();
};

/**
 * @brief create a list structure
 * 
 * @param freeFunc function to free itens from the list
 * @param printFunc function to print itens in the list
 * @return list_t* list structure
 */
list_t *create_list(void (*freeFunc) (), void (*printFunc) ()){
    //initializing variables
    list_t *l = (list_t *)malloc(sizeof(list_t));
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    l->free = freeFunc;
    l->print = printFunc;

    return  l;
}

/**
 * @brief returns the size from the list
 * 
 * @param l list structure
 * @return int size of said list
 */
int list_size(list_t *l){
    return l->size;
}

/**
 * @brief inserts a item in the list
 * 
 * @param l list structure
 * @param data item to be added to the list
 */
void insert_in_list(list_t *l, void *data){
    node_t *n = (node_t *)malloc(sizeof(node_t));
    n->data = data;
    n->next = NULL;

    if(l->head == NULL){
        //inserting the first item in the list
        l->head = n;
        l->tail = n;
    }
    else{
        //inserting other itens in the list
        l->tail->next = n;
        l->tail = n;
    }
    l->size++;
}

/**
 * @brief removes a item from the list and returns it to the user
 * 
 * @param l list structure
 * @return void* item to be removed and returned
 */
void *remove_from_list(list_t *l){
    if(l->head == NULL)
        return NULL;
    
    node_t *n = l->head;
    void *data = n->data;
    //moving the list head to the next element
    l->head = n->next;
    free(n);

    return data;
}

/**
 * @brief prints a item in the list
 * 
 * @param l list structure
 */
void print_list(list_t *l){
    if(l->head == NULL){
        printf("Empty List\n");
        return;
    }

    node_t *n = l->head;
    while(n != NULL){
        //here we check which item we are printing in the list
        //-2 represents a single element in the list
        //-1 represents the first element in the list
        //0 represents a element in the middle in the list
        //1 represents the last element in the list
        if(l->head == l->tail)
            l->print(n->data, -2);
        else if(n == l->head)
            l->print(n->data, -1);
        else if(n->next != NULL)
            l->print(n->data, 0);
        else
            l->print(n->data, 1);
        n = n->next;
    }
    printf("\n");
}

/**
 * @brief destroys a list structure, deallocating memory
 * 
 * @param l list structure
 */
void destroy_list(list_t *l){
    node_t *n = l->head;
    while(n != NULL){
        if(l->free != NULL)
            l->free(n->data);
        l->head = n->next;
        free(n);
        //progressing through list
        n = l->head;
    }
    free(l);
}