#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

/**
 * @brief queue struct (designed only to receive integers)
 * 
 */
typedef struct queue{
    int first, last, size, max;
    person_t contents[MAX_SIZE];
}queue_t;

/**
 * @brief creates and initializes a queue struct, initializing the size of the struct based on the user's input
 * 
 * @param contentSize size of the queue
 * @return queue_t* pointer to a queue struct
 */
queue_t *create(){
    queue_t *q;
    q = (queue_t *)malloc(sizeof(queue_t));
    q->first = 0;
    q->last = 0;
    q->size = 0;
    q->max = MAX_SIZE;

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
 * @brief adds a person to the queue
 * 
 * @param q queue struct
 * @param name name of the person
 * @param age age of the person
 * @param hasIllness whether a person has a illness or not
 * @return int returns 1 if it was sucessfull, 0 if it wasn't
 */
int enqueue(queue_t *q, char *name, int age, int hasIllness){
    if(isFull(q) == 1)
        return 0;

    //allocating dinamic space for the name string
    q->contents[q->last].name = (char *)malloc((strlen(name)+1) * sizeof(char));
    strcpy(q->contents[q->last].name, name);
    q->contents[q->last].age = age;
    q->contents[q->last].hasIllness = hasIllness;

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
int dequeue(queue_t *q, char **name, int *age, int *hasIllness){
    if(isEmpty(q) == 1)
        return 0;
    
    //allocating dinamic space for the name string
    *name = (char *)malloc((strlen(q->contents[q->first].name)+1) * sizeof(char));
    strcpy(*name, q->contents[q->first].name);
    *age = q->contents[q->first].age;
    *hasIllness = q->contents[q->first].hasIllness;

    //freeing the name from the person struct
    free(q->contents[q->first].name);
    //making a circular vector
    q->first = (q->first + 1) % q->max;
    q->size--;

    return 1;
}

/**
 * @brief destroys a queue
 * 
 * @param q queue struct
 */
void destroy(queue_t *q){
    while(isEmpty(q) != 1){
        char *nameTrash = NULL;
        int ageTrash, hasIllnessTrash;

        dequeue(q, &nameTrash, &ageTrash, &hasIllnessTrash);
        free(nameTrash);
    }
    free(q);
}