#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct TreeSetup setup_t;
typedef struct BinaryTree btree_t;

setup_t **create_setup(int NodeAmount);
void destroy_setup(setup_t **s, int size);
btree_t *create_tree(setup_t **s);
int sum_of_child_nodes(btree_t *t);
void destroy_tree(btree_t *t);

#endif