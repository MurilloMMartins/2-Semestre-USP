#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

struct node{
    int value;
    node_t *left, *right;
};

void print_pre_order(node_t *root);
void print_in_order(node_t *root);
void print_post_order(node_t *root);

/**
 * @brief initializes and returns a binary search tree(BST)
 * 
 * @return BST_t* BST structure
 */
BST_t *create_bst(){
    BST_t *tree = malloc(sizeof(BST_t *));
    tree->root = NULL;

    return tree;
}

/**
 * @brief inserts a element in a BST
 * 
 * @param root BST's root
 * @param data data to be inserted
 */
void insert_bst(node_t **root, int data){
    //inserting the element in the available space
    if(*root == NULL){
        *root = malloc(sizeof(node_t));
        (*root)->value = data;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }
    else if(data == (*root)->value)         //if the element already exists
        return;
    else if(data < (*root)->value)
        insert_bst(&(*root)->left, data);   //going to the left branch of the tree
    else
        insert_bst(&(*root)->right, data);  //going to the left branch of the tree
}

/**
 * @brief prints the contents of a BST in a certain order
 * 
 * @param root root of the BST
 * @param order order to be printed
 */
void print_bst(node_t *root, int order){
    //if the tree is empty
    if(root == NULL){
        printf("VAZIA\n");
        return;
    }

    //deciding the order to print
    switch(order){
        case -1:
            print_pre_order(root);
            break;
        case 0:
            print_in_order(root);
            break;
        case 1:
            print_post_order(root);
            break;
    }
    printf("\n");
}

/**
 * @brief prints a BST in pre-order
 * 
 * @param root BST root
 */
void print_pre_order(node_t *root){
    if(root == NULL)
        return;
    
    printf("%d ", root->value);
    print_pre_order(root->left);
    print_pre_order(root->right);
}

/**
 * @brief prints a BST in order
 * 
 * @param root BST root
 */
void print_in_order(node_t *root){
    if(root == NULL)
        return;

    print_in_order(root->left);
    printf("%d ", root->value);
    print_in_order(root->right);
}

/**
 * @brief prints a BST in post-order
 * 
 * @param root BST root
 */
void print_post_order(node_t *root){
    if(root == NULL)
        return;
    
    print_post_order(root->left);
    print_post_order(root->right);
    printf("%d ", root->value);
}

/**
 * @brief deallocates memory from a BST
 * 
 * @param root 
 */
void destroy_bst(node_t *root){
    if(root == NULL)
        return;

    destroy_bst(root->left);
    destroy_bst(root->right);
    free(root);
}
