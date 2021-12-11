#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

typedef struct node node_t;
struct node{
    char *data;
    node_t *next;
};

struct indexVector{
    node_t **array;
    int size;
};

struct list{
    node_t *head, *tail;
};

/**
 * @brief create a sorted list structure
 * 
 * @return list_t* 
 */
list_t *create_list(){
    list_t *l = (list_t *)malloc(sizeof(list_t));
    //initializing variables
    l->head = NULL;
    l->tail = NULL;

    return l;
}

/**
 * @brief inserts a item in the list
 * 
 * @param l list struct
 * @param data data to be inserted
 */
void insert_in_list(list_t *l, char *data){
    //creating a node that will be inserted in the list
    node_t *nAdd = (node_t *)malloc(sizeof(node_t));
    nAdd->data = (char *)malloc((strlen(data)+1) * sizeof(char));
    strcpy(nAdd->data, data);

    //this happens if this is the first insertion in the list
    if(l->head == NULL){
        nAdd->next = NULL;
        l->head = nAdd;
        l->tail = nAdd;
        return;
    }

    //inserting a element before the first element
    if(l->head->data[0] >= nAdd->data[0]){
        nAdd->next = l->head;
        l->head = nAdd;
        return;
    }

    //inserting a element after the last element
    if(l->tail->data[0] < nAdd->data[0]){
        l->tail->next = nAdd;
        l->tail = nAdd;
        l->tail->next = NULL;
        return;
    }

    //inserting a element in the middle
    node_t *nCurr = l->head;
    node_t *nNext = nCurr->next;
    while(nAdd->data[0] > nCurr->data[0] && nAdd->data[0] > nNext->data[0]){
        //progressing through the list
        nCurr = nCurr->next;
        nNext = nNext->next;
    }

    nCurr->next = nAdd;
    nAdd->next = nNext;
}

/**
 * @brief searches a list using the index vector
 * 
 * @param v index vector
 * @param data data to be searched
 * @return int -1 if the data isn't in the list, otherwise it returns the amount of itens if went 
 * through while searching
 */
int search_list(index_vector_t *v, char *data){
    //"data[0]-'a'" is used to find the index of the index vector
    node_t *aux = v->array[data[0] - 'a'];
    if(aux == NULL)
        return -1;

    //initializing variables
    int path = 0;
    char control = aux->data[0];
    while(control == data[0] && aux != NULL){
        if(strcmp(data, aux->data) == 0)
            return path;
        path++;
        //progressing through the list
        aux = aux->next;
        if(aux != NULL)
            control = aux->data[0];
    }

    return -1;
}

/**
 * @brief prints the first 3 elements of a linked list
 * 
 * @param l linked list struct
 */
void print_list_head(list_t *l){
    node_t *aux = l->head;
    for(int i = 0; i < 3; i++){
        if(aux != NULL){
            printf("%s\n", aux->data);
            aux = aux->next;
        }
    }
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
        l->head = n->next;
        free(n->data);
        free(n);
        n = l->head;
    }
    free(l);
}

/**
 * @brief creates a index vector struct based on a given list
 * 
 * @param l list struct
 * @return index_vector_t* index vector struct
 */
index_vector_t *create_index_vector(list_t *l){
    //initializing variables and allocating memory
    index_vector_t *v = (index_vector_t *)malloc(sizeof(index_vector_t));
    v->array = (node_t **)malloc(26 * sizeof(node_t *));
    v->size = 1;
    for(int i = 0; i < 26; i++){
        v->array[i] = NULL;
    }

    //initializing control variables
    node_t *aux = l->head;
    char control = l->head->data[0];
    //including first element in the list in the array
    v->array[control - 'a'] = l->head;
    while(aux != NULL){
        char curr = control;
        //finding the next key in the list to insert into the array
        while(curr == control && aux != NULL){
            aux = aux->next;
            if(aux != NULL){
                control = aux->data[0];
            }
        }

        //inserting new key and incrementing size
        if(aux != NULL){
            v->array[control - 'a'] = aux;
            v->size++;
        }
    }

    return v;
}

/**
 * @brief prints the size of the index vector struct
 * 
 * @param v index vector struct
 */
void print_index_size(index_vector_t *v){
    printf("%d\n", v->size);
}

/**
 * @brief deallocates memory from a index vector struct
 * 
 * @param v index vector struct
 */
void destroy_index_vector(index_vector_t *v){
    free(v->array);
    free(v);
}