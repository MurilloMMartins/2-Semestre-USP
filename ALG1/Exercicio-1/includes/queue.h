#ifndef QUEUE_H
#define QUEUE_H

#define queueSize 200

typedef struct queue queue_t;

queue_t *create();
int isEmpty(queue_t *q);
int isFull(queue_t *q);
int enqueue(queue_t *q, char *data);
int dequeue(queue_t *q, char **data);
void destroy(queue_t *q);

#endif