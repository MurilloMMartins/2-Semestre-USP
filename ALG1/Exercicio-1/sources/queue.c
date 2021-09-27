#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

/**
 * @brief queue struct (designed only to receive char * or strings), it has a maximum capacity of 200 available spaces
 * 
 */
typedef struct queue{
    int first, last, size;
    char *contents[queueSize];
}queue_t;

/**
 * @brief creates and initializes a queue struct
 * 
 * @return queue_t* pointers to the queue struct
 */
queue_t *create(){
    queue_t *q;
    q = (queue_t *)malloc(sizeof(queue_t));
    q->first = 0;
    q->last = 0;
    q->size = 0;

    return q;
}

/**
 * @brief checks if a queue is empty
 * 
 * @param q q struct
 * @return int 1 for true or 0 for false
 */
int isEmpty(queue_t *q){
    if(q->size == 0)
        return 1;
    return 0;
}

/**
 * @brief checks if a queue is full
 * 
 * @param q 
 * @return int 1 for true or 0 for false
 */
int isFull(queue_t *q){
    if(q->size == queueSize)
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
int enqueue(queue_t *q, char *data){
    if(isFull(q) == 1 || data == NULL)
        return 0;

    //allocates strings size
    int stringSize = strlen(data) + 1;
    q->contents[q->last] = (char *)malloc(stringSize * sizeof(char));
    strcpy(q->contents[q->last], data);

    //using this to make a circular vector
    q->last = (q->last + 1) % queueSize;
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
int dequeue(queue_t *q, char **data){
    if(isEmpty(q) == 1)
        return 0;

    //allocates string size
    int stringSize = strlen(q->contents[q->first]) + 1;
    *data = (char *)malloc(stringSize * sizeof(char));
    strcpy(*data, q->contents[q->first]);

    //freeing the content from the queue
    free(q->contents[q->first]);
    //using this to make a circular vector
    q->first = (q->first + 1) % queueSize;
    q->size--;

    return 1;
}

//destroys an empty queue
void destroy(queue_t *q){
    free(q);
}
