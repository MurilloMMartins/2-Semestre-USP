#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct node node_t;

struct node {
    void *data;
    node_t *next;
};

struct queue {
    node_t *head;
    node_t *tail;
};

queue_t *create_queue(){
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));

    q->head = NULL;
    q->tail = NULL;
    return q;
}

void destroy_queue(queue_t *q){
    if (q != NULL) {
        node_t *aux = q->head;

        while (aux != NULL) {
            q->head = aux->next;
            free(aux);
            aux = q->head;
        }
        free(q);
    }
}

void insert_queue(queue_t *q, void *data){
    node_t *aux = malloc(sizeof(node_t));

    aux->data = data;
    aux->next = NULL;

    //inserting first element
    if (q->head == NULL) {
        q->head = aux;
        q->tail = aux;
    }
    else
        q->tail->next = aux;

    q->tail = aux;
}

int is_empty(queue_t *q){
    if (q == NULL) return 0;

    if (q->head == NULL) return 1;

    return 0;
}

void *pop_queue(queue_t *q){
    node_t *n = q->head;

    if (n != NULL) {
        if (q->tail == q->head)
            q->tail = NULL;

        q->head = q->head->next;

        void *aux = n->data;
        free(n);
        
        return aux;
    }

    return NULL;
}