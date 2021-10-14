#ifndef LIST_H
#define LIST_H

typedef struct list list_t;

list_t *create();
void destroy(list_t *l);
void insert(list_t *l, int x);
int size(list_t *l);
void printList(list_t *l);
void rotate(list_t *l);

#endif