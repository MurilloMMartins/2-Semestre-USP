#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct list list_t;
typedef struct indexVector index_vector_t;

list_t *create_list();
void insert_in_list(list_t *l, char *data);
int search_list(index_vector_t *v, char *data);
void print_list_head(list_t *l);
void destroy_list(list_t *l);

index_vector_t *create_index_vector(list_t *l);
void print_index_size(index_vector_t *v);
void destroy_index_vector(index_vector_t *v);

#endif