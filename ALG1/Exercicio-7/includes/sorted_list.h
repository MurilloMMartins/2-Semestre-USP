#ifndef SORTED_LIST_H
#define SORTED_LIST_H

typedef struct list list_t;

list_t *create_list(void (*freeFunc)(), int (*cmpFunc)(), void (*printFunc)());
void insert_in_list(list_t *l, void *data);
void remove_from_list(list_t *l, void *data);
void print_list(list_t *l);
void destroy_list(list_t *l);

#endif