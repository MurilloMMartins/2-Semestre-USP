#ifndef SKIP_LIST_H
#define SKIP_LIST_H

typedef struct skiplist skip_t;

skip_t *create_list(int maxLevel);
int insert_in_list(skip_t *sl, void *data, int (*compareFunc) (), void (*freeFunc) ());
int change_data_in_list(skip_t *sl, void *data, int (*compareFunc) (), void (*freeFunc) ());
int remove_data_from_list(skip_t *sl, void *data, int (*compareFunc) (), void (*freeFunc) ());
int search_in_list(skip_t *sl, void *data, int (*compareFunc) (), void (*printFunc) (), void (*freeFunc) ());
int print_list(skip_t *sl, void *data, int (*compareFunc) (), void (*printFunc) ());
void destroy_list(skip_t *sl, void (*freeFunc) ());

#endif