#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue queue_t;

/**
 * @brief creates and returns a queue
 * 
 * @return queue_t* queue
 */
queue_t *create_queue();

/**
 * @brief inserts a element in the queue
 * 
 * @param q queue
 * @param data element
 */
void insert_queue(queue_t *q, void *data);

/**
 * @brief destroy a queue
 * 
 * @param q queue
 */
void destroy_queue(queue_t *q);

/**
 * @brief returns if a queue is empty
 * 
 * @param q queue
 * @return int return
 */
int is_empty(queue_t *q);

/**
 * @brief pops a element from a queue
 * 
 * @param q queue
 * @return void* element that was removed
 */
void *pop_queue(queue_t *q);

#endif