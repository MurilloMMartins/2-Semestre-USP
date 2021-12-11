#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

struct TreeSetup{
    int ID, value, left, right;
};

typedef struct node node_t;
struct node{
    int value;
    node_t *left, *right;
};

struct BinaryTree{
    node_t *root;
};

void fill_tree(node_t *n, setup_t **s, int ID);
void deallocate_tree(node_t *n);
int is_sum_of_nodes(node_t *n);

/**
 * @brief creates the setup for a binary tree
 * 
 * @param NodeAmount amount of nodes in the tree
 * @return setup_t** setup structure
 */
setup_t **create_setup(int NodeAmount){
    setup_t **s = malloc(sizeof(setup_t *) * NodeAmount);

    for(int i = 0; i < NodeAmount; i++){
        s[i] = malloc(sizeof(setup_t));
        scanf("%d %d %d %d", &s[i]->ID, &s[i]->value, &s[i]->left, &s[i]->right);
    }

    return s;
}

/**
 * @brief deallocates memory from a setup struct
 * 
 * @param s setup structure
 * @param size amount of nodes in the tree
 */
void destroy_setup(setup_t **s, int size){
    for(int i = 0; i < size; i++){
        free(s[i]);
    }
    free(s);
}

/**
 * @brief creates a binary tree based on the setup data
 * 
 * @param s setup structure
 * @return btree_t* binary tree structure
 */
btree_t *create_tree(setup_t **s){
    btree_t *t = malloc(sizeof(btree_t));
    t->root = malloc(sizeof(node_t));

    fill_tree(t->root, s, 0);

    return t;
}

/**
 * @brief fills the binary three based on the setup data
 * 
 * @param n current node
 * @param s setup structure that contains data
 * @param ID setup ID, so we can identify what data will be on each branch/leaf
 */
void fill_tree(node_t *n, setup_t **s, int ID){
    //initializing all values for current node
    n->value = s[ID]->value;
    n->left = NULL;
    n->right = NULL;

    if(s[ID]->left != -1){
        //allocating memory and filling left node
        n->left = malloc(sizeof(node_t));
        fill_tree(n->left, s, s[ID]->left);
    }
    
    if(s[ID]->right != -1){
        //allocating memory and filling right node
        n->right = malloc(sizeof(node_t));
        fill_tree(n->right, s, s[ID]->right);
    }
}

/**
 * @brief returns whether or all the nodes of a tree are equal to the sum of each of it's child's values
 * 
 * @param t tree structure
 * @return int 0 for false, 1 for true
 */
int sum_of_child_nodes(btree_t *t){
    return is_sum_of_nodes(t->root);
}

/**
 * @brief returns whether or all the nodes of a tree are equal to the sum of each of it's child's values
 * 
 * @param n current node
 * @return int 0 for false, 1 for true
 */
int is_sum_of_nodes(node_t *n){
    //if all nodes are NULL then, we are at a leaf
    if(n->left == NULL && n->right == NULL)
        return 1;

    //checking if we have a left/right node and if we do, add the values of them
    int sum = 0;
    if(n->left != NULL)
        sum += n->left->value;
    
    if(n->right != NULL)
        sum += n->right->value;

    if(n->value == sum){
        int left = 1;
        int right = 1;
        //recursivelly checking if the left and right nodes of our tree are in this state
        if(n->left != NULL)
            left = is_sum_of_nodes(n->left);
        if(n->right != NULL)
            right = is_sum_of_nodes(n->right);
        
        return left && right;
    }

    //we only reach this if the current node isn't the sum of it's children
    return 0;
}

/**
 * @brief destroys a binary tree structure
 * 
 * @param t binary tree structure
 */
void destroy_tree(btree_t *t){
    deallocate_tree(t->root);
    free(t);
}

/**
 * @brief deallocates memory recursivelly from a binary tree
 * 
 * @param n current node
 */
void deallocate_tree(node_t *n){
    if(n->left != NULL)
        deallocate_tree(n->left);
    if(n->right != NULL)
        deallocate_tree(n->right);
    free(n);
}
