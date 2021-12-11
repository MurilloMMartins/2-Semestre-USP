#ifndef TREAP_H
#define TREAP_H

typedef struct node node_t;
typedef struct treap_tree{
    node_t *root;
}treap_t;

/**
 * @brief creates a treap tree
 * 
 * @return treap_t* treap
 */
treap_t *create_treap();

/**
 * @brief inserts a element in a treap queue acording to its value and priority
 * 
 * @param t treap tree
 * @param key value of the item
 * @param priority priority of said item
 * @return int if the element was inserted sucessfull, return 1
 */
int insert_treap(treap_t *t, int key, int priority);

/**
 * @brief removes a element from a treap tree
 * 
 * @param t treap tree
 * @param key element to be removed
 * @return int return 1 if a element was sucessfully removed
 */
int remove_treap(treap_t *t, int key);

/**
 * @brief searches a element in a treap tree
 * 
 * @param root searchs a element in a treap tree
 * @param key key to be searched
 * @return int returns 1 if the element is in the list
 */
int search_treap(node_t *root, int key);

/**
 * @brief prints a treap tree according to a certain order. 0 - prints in order. 1 - prints postorder. 2 - prints preorder. 3 - prints in width
 * 
 * @param t treap tree
 * @param mode mode
 */
void print_treap(treap_t *t, int mode);

/**
 * @brief destroys a treap tree
 * 
 * @param t treap tree
 */
void destroy_treap(treap_t *t);

#endif