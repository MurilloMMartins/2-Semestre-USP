#include <stdio.h>
#include <stdlib.h>
#include "treap.h"
#include "queue.h"

struct node{
    node_t *left, *right;
    int key, priority;
};

void insert_node(node_t *n, node_t **curr);
void LL_rotate(node_t **parent);
void RR_rotate(node_t **parent);
node_t *search(node_t *root, int key);
void destroy(node_t *root);
void remove_tree(node_t **curr, int key);
void print_order(node_t *root);
void print_preorder(node_t *root);
void print_postorder(node_t *root);
void print_width(node_t *root);

treap_t *create_treap(){
    treap_t *t = malloc(sizeof(treap_t));
    t->root = NULL;

    return t;
}

int insert_treap(treap_t *t, int key, int priority){
    //searching if a element exists
    if(search_treap(t->root, key))
        return 0;

    //allocates the necessary memory
    node_t *n = malloc(sizeof(node_t));
    n->key = key;
    n->priority = priority;
    n->left = NULL;
    n->right = NULL;

    if(t->root == NULL){
        t->root = n;
        return 1;
    }

    insert_node(n, &t->root);

    return 1;
}

/**
 * @brief inserts a node in a treap tree
 * 
 * @param n node to be inserted
 * @param curr node from the tree
 */
void insert_node(node_t *n, node_t **curr){
    //placing the new node in the right place
    if((*curr) == NULL){
        (*curr) = n;
        return;
    }

    //checking whether we navigate throught the left or right branch in the tree
    if((*curr)->key > n->key){
        insert_node(n, &(*curr)->left);
        //rotating if our tree isn't in order
        if((*curr)->left->priority > (*curr)->priority)
            RR_rotate(curr);
    }
    if((*curr)->key < n->key){
        insert_node(n, &(*curr)->right);
        //rotating if our tree isn't in order
        if((*curr)->right->priority > (*curr)->priority)
            LL_rotate(curr);
    }
}

/**
 * @brief rotates a element to the left in the tree
 * 
 * @param parent node to be rotated
 */
void LL_rotate(node_t **parent){
    node_t *right = (*parent)->right;
    (*parent)->right = right->left;
    right->left = (*parent);
    (*parent) = right;
}

/**
 * @brief rotates a element to the right in the tree
 * 
 * @param parent node to be rotated
 */
void RR_rotate(node_t **parent){
    node_t *left = (*parent)->left;
    (*parent)->left = left->right;
    left->right = (*parent);
    (*parent) = left;
}

int remove_treap(treap_t *t, int key){
    //searches if a element exists
    if(!(search(t->root, key)))
        return 0;

    remove_tree(&(t->root), key);

    return 1;
}

/**
 * @brief removes a element from the tree
 * 
 * @param curr tree node
 * @param key key for the element that will be removed
 */
void remove_tree(node_t **curr, int key){
    //checking to find the node that contains the key
    if((*curr)->key > key)
        remove_tree(&(*curr)->left, key);
    else if((*curr)->key < key)
        remove_tree(&(*curr)->right, key);
    else{
        //rotates to the left until the right branch of a node is NULL
        if((*curr)->right != NULL){
            LL_rotate(curr);
            remove_tree(&(*curr)->left, key);
        }
        else{
            node_t *aux = *curr;
            (*curr) = (*curr)->left;
            free(aux);
        }
    }
}

int search_treap(node_t *root, int key){
    node_t *n = search(root, key);
    if(n == NULL)
        return 0;
    return 1;
}

/**
 * @brief searches a element in the tree and returns the node containing said element
 * 
 * @param root 
 * @param key 
 * @return node_t* 
 */
node_t *search(node_t *root, int key){
    if(root == NULL)
        return NULL;

    if(root->key == key)
        return root;
    if(root->key > key)
        return search(root->left, key);
    if(root->key < key)
        return search(root->right, key);

    return NULL;
}

void print_treap(treap_t *t, int mode){
    if(t->root == NULL)
        return;
    
    //deciding which mode to print in
    switch(mode){
        case 0:
            print_order(t->root);
            break;
        case 1:
            print_postorder(t->root);
            break;
        case 2:
            print_preorder(t->root);
            break;
        case 3:
            print_width(t->root);
            break;
    }
    printf("\n");
}

/**
 * @brief prints a tree in order
 * 
 * @param root tree node
 */
void print_order(node_t *root){
    if(root == NULL)
        return;

    print_order(root->left);
    printf("(%d, %d) ", root->key, root->priority);
    print_order(root->right);
}

/**
 * @brief prints a tree in pre-order
 * 
 * @param root tree node
 */
void print_preorder(node_t *root){
    if(root == NULL)
        return;

    printf("(%d, %d) ", root->key, root->priority);
    print_preorder(root->left);
    print_preorder(root->right);
}

/**
 * @brief prints a tree in post-order
 * 
 * @param root tree node
 */
void print_postorder(node_t *root){
    if(root == NULL)
        return;

    print_postorder(root->left);
    print_postorder(root->right);
    printf("(%d, %d) ", root->key, root->priority);
}

/**
 * @brief prints all the elements of a tree in each level in that order
 * 
 * @param root tree node
 */
void print_width(node_t *root){
    queue_t *f = create_queue();

    insert_queue(f, root);
    while(is_empty(f) == 0){
        node_t *n = pop_queue(f);
        printf("(%d, %d) ", n->key, n->priority);
        if(n->left != NULL)
            insert_queue(f, n->left);
        if(n->right != NULL)
            insert_queue(f, n->right);
    }

    destroy_queue(f);
}

void destroy_treap(treap_t *t){
    destroy(t->root);
    free(t);
}

/**
 * @brief destroys a tree struct
 * 
 * @param root tree node
 */
void destroy(node_t *root){
    if(root == NULL)
        return;

    destroy(root->left);
    destroy(root->right);

    free(root);
}