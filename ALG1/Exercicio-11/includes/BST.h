#ifndef BST_H
#define BST_H

typedef struct node node_t;
typedef struct bst{
    node_t *root;
} BST_t;

BST_t *create_bst();
void insert_bst(node_t **root, int data);
void print_bst(node_t *root, int order);
void destroy_bst(node_t *root);

#endif