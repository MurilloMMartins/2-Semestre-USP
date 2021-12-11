/**
 * @file main.c
 * @author Murillo Moraes Martins (12701599)
 * @brief this program build a binary tree based on the user's input and prints whether the value of
 * all the nodes in said tree is equal to the sum of its children
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include "binary_tree.h"

int main(int argc, char *argv[]){

    int size;
    scanf(" %d", &size);
    setup_t **setup = create_setup(size);
    btree_t *tree = create_tree(setup);
    
    switch(sum_of_child_nodes(tree)){
        case 1:
            printf("VERDADEIRO\n");
            break;
        case 0:
            printf("FALSO\n");
            break;
    }

    destroy_tree(tree);
    destroy_setup(setup, size);

    /*
        return
       /      \
      0        0
    */
    return 0;
}