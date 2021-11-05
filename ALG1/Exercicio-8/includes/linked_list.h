#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct list list_t;

list_t *create_list(void (*freeFunc) (),  void (*printFunc) ());
int list_size(list_t *l);
void insert_in_list(list_t *l, void *data);
void *remove_from_list(list_t *l);
void print_list(list_t *l);
void destroy_list(list_t *l);

#endif