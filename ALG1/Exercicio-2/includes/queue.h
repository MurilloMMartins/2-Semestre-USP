#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue queue_t;

queue_t *create(int size);
int isEmpty(queue_t *q);
int isFull(queue_t *q);
int enqueue(queue_t *q, int data);
int dequeue(queue_t *q, int *data);
void destroy(queue_t *q);

#endif