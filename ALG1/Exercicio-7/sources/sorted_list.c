#include <stdio.h>
#include <stdlib.h>
#include "sorted_list.h"

typedef struct node node_t;
struct node{
    void *data;
    node_t *next;
};

struct list{
    node_t *head, *tail;
    void (*free) (void *);
    int (*compare) (void *, void *);
    void (*print) (void *);
};

/**
 * @brief create a sorted list structure
 * 
 * @param freeFunc function that frees the data
 * @param cmpFunc function that compares data
 * @param printFunc function that prints data
 * @return list_t* 
 */
list_t *create_list(void (*freeFunc)(void *), int (*cmpFunc)(void *, void *), void (*printFunc)(void *)){
    list_t *l = (list_t *)malloc(sizeof(list_t));
    //initializing variables
    l->head = NULL;
    l->tail = NULL;
    l->free = freeFunc;
    l->compare = cmpFunc;
    l->print = printFunc;

    return l;
}

/**
 * @brief inserts a item in the list
 * 
 * @param l list struct
 * @param data data to be inserted
 */
void insert_in_list(list_t *l, void *data){
    //creating a node that will be inserted in the list
    node_t *nAdd = (node_t *)malloc(sizeof(node_t));
    nAdd->data = data;

    //this happens if this is the first insertion in the list
    if(l->head == NULL){
        nAdd->next = NULL;
        l->head = nAdd;
        l->tail = nAdd;
        return;
    }

    //inserting a element before the first element
    if(l->compare(nAdd->data, l->head->data) == -1){
        nAdd->next = l->head;
        l->head = nAdd;
        return;
    }

    //inserting a element after the last element
    if(l->compare(nAdd->data, l->tail->data) == 1){
        l->tail->next = nAdd;
        l->tail = nAdd;
        l->tail->next = NULL;
        return;
    }

    //inserting a element in the middle
    node_t *nCurr = l->head;
    node_t *nNext = nCurr->next;
    while(l->compare(nAdd->data, nCurr->data) != 1 || l->compare(nAdd->data, nNext->data) != -1){
        //checking if this element already exists in this list
        if(l->compare(nAdd->data, nCurr->data) == 0 || l->compare(nAdd->data, nNext->data) == 0){
            printf("INVALIDO\n");
            if(l->free != NULL)
                l->free(nAdd->data);
            free(nAdd);
            return;
        }
        //progressing through the list
        nCurr = nCurr->next;
        nNext = nNext->next;
    }

    nCurr->next = nAdd;
    nAdd->next = nNext;
}

/**
 * @brief removes an element from the list
 * 
 * @param l list structure
 * @param data data that will be removed from the structure
 */
void remove_from_list(list_t *l, void *data){
    //this happens if you try to remove a element from a empty list
    if(l->head == NULL){
        printf("INVALIDO\n");
        if(l->free != NULL)
            l->free(data);
        return;
    }

    //removing the first element from the list
    if(l->compare(data, l->head->data) == 0){
        if(l->free != NULL){
            l->free(l->head->data);
            l->free(data);
        }
        node_t *aux = l->head;
        l->head = l->head->next;
        free(aux);
        return;
    }

    node_t *nPrev = l->head;
    node_t *nCurr = l->head->next;
    //this if is important because it prevents the program from acessing non-allocated memory
    //this would only be NULL if we have 1 element in the list
    if(nCurr != NULL){
        while(nCurr->next != NULL){
            //removing a element from the middle of the list
            if(l->compare(data, nCurr->data) == 0){
                nPrev->next = nCurr->next;
                if(l->free != NULL){
                    l->free(nCurr->data);
                    l->free(data);
                }
                free(nCurr);
                return;
            }
            //progressing through the list
            nCurr = nCurr->next;
            nPrev = nPrev->next;
        }
        
        //removing a element from the end of the list
        if(l->compare(data, nCurr->data) == 0){
            l->tail = nPrev;
            l->tail->next = NULL;
            if(l->free != NULL){
                l->free(nCurr->data);
                l->free(data);
            }
            free(nCurr);
            return;
        }
    }

    //this only prints if we don't find any elements to remove
    printf("INVALIDO\n");
    if(l->free != NULL)
    l->free(data);
    
}

/**
 * @brief prints the elements from a list
 * 
 * @param l list struct
 */
void print_list(list_t *l){
    //checks if a list is empty
    if(l->head == NULL){
        printf("VAZIA\n");
        return;
    }

    //printing list elements
    node_t *n = l->head;
    while(n != NULL){
        l->print(n->data);
        n = n->next;
    }
    printf("\n");
}

/**
 * @brief free's all the data from a list
 * 
 * @param l list struct
 */
void destroy_list(list_t *l){
    node_t *n = l->head;
    //progressing through the list
    while(n != NULL){
        if(l->free != NULL)
            l->free(n->data);
        l->head = n->next;
        free(n);
        n = l->head;
    }
    free(l);
}
