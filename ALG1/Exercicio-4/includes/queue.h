#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE 100

/**
 * @brief struct that will have a person's info
 * 
 */
typedef struct person{
    char *name;
    int age;
    int hasIllness;
}person_t;

typedef struct queue queue_t;

queue_t *create();
int isEmpty(queue_t *q);
int isFull(queue_t *q);
int enqueue(queue_t *q, char *name, int age, int hasIllness);
int dequeue(queue_t *q, char **name, int *age, int *hasIllness);
void destroy(queue_t *q);

#endif