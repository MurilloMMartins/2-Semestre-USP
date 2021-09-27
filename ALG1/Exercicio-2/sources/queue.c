#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/**
 * @brief queue struct (designed only to receive integers)
 * 
 */
typedef struct queue{
    int first, last, size, max;
    int *contents;
}queue_t;

/**
 * @brief creates and initializes a queue struct, initializing the size of the struct based on the user's input
 * 
 * @param contentSize size of the queue
 * @return queue_t* pointer to a queue struct
 */
queue_t *create(int contentSize){
    queue_t *q;
    q = (queue_t *)malloc(sizeof(queue_t));
    q->contents = (int *)malloc(contentSize * sizeof(int));
    q->first = 0;
    q->last = 0;
    q->size = 0;
    q->max = contentSize;

    return q;
}

/**
 * @brief checks if a queue is empty
 * 
 * @param q queue struct
 * @return int returns 1 it's empty, 0 otherwise
 */
int isEmpty(queue_t *q){
    if(q->size == 0)
        return 1;
    return 0;
}

/**
 * @brief checks if a queue is full
 * 
 * @param q queue struct
 * @return int returns 1 if it's full, 0 otherwise
 */
int isFull(queue_t *q){
    if(q->size == q->max)
        return 1;
    return 0;
}

/**
 * @brief adds a element to the queue
 * 
 * @param q queue struct
 * @param data element to be added to the queue
 * @return int returns 1 if it was sucessfull, 0 if it wasn't
 */
int enqueue(queue_t *q, int data){
    if(isFull(q) == 1)
        return 0;
    
    q->contents[q->last] = data;
    q->last = (q->last + 1) % q->max;
    q->size++;
    return 1;
}

/**
 * @brief takes a element out of the queue
 * 
 * @param q queue struct
 * @param data element to be removed from the queue
 * @return int returns 1 if it was sucessfull, 0 if it wasn't
 */
int dequeue(queue_t *q, int *data){
    if(isEmpty(q) == 1)
        return 0;
    
    *data = q->contents[q->first];
    q->first = (q->first + 1) % q->max;
    q->size--;
    return 1;
}

/**
 * @brief destroys an empty queue
 * 
 * @param q queue struct
 */
void destroy(queue_t *q){
    if(q != NULL){
        free(q->contents);
        free(q);
    }
}
