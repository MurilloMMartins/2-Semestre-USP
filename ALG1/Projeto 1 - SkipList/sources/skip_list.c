#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "skip_list.h"

typedef struct node node_t;
struct node{
    void *data;
    node_t **next;
};

struct skiplist{
    node_t *head;
    int level;
    int maxLevel;
};

/**
 * @brief create a node structure
 * 
 * @param data node data
 * @param level max level of this node in the skip list
 * @return node_t* node struct
 */
node_t *create_node(void *data, int level){
    node_t *n = (node_t *)malloc(sizeof(node_t));
    n->data = data;
    //allocating and initializing the next node pointers
    n->next = (node_t **)malloc(sizeof(node_t *) * (level+1));
    for(int i = 0; i <= level; i++)
        n->next[i] = NULL;

    return n;
}

/**
 * @brief create a list structure
 * 
 * @param maxLevel 
 * @return skip_t* 
 */
skip_t *create_list(int maxLevel){
    //initializing rand seed
    srand(time(NULL));
    
    skip_t *sl = (skip_t *)malloc(sizeof(skip_t));
    sl->head = create_node(NULL, maxLevel);
    sl->level = 0;
    sl->maxLevel = maxLevel;

    return sl;
}

/**
 * @brief generates a random level for a skip list node using a coin flip
 * 
 * @param maxLevel max level
 * @return int random level
 */
int randomLevel(int maxLevel){
    int level = 0;
    int coinFlip = 1;
    while(coinFlip % 2 != 0){
        coinFlip = rand() % 2;
        level = (level + 1) % maxLevel;
    }

    return level;
}

/**
 * @brief inserts a item in the skip list
 * 
 * @param sl skip list struct
 * @param data data to be inserted
 * @param compareFunc function to compare data elements
 * @param freeFunc function to free data
 * @return int returns whether the element was already unique to the list or not
 */
int insert_in_list(skip_t *sl, void *data, int (*compareFunc) (), void (*freeFunc) ()){

    node_t *curr = sl->head;
    node_t **update = (node_t **)malloc((sl->maxLevel + 1) * sizeof(node_t *));

    //initializing update variable
    for(int i = 0; i <= sl->maxLevel; i++)
        update[i] = NULL;

    //running update through elements and getting those that have the next pointer to a data bigger than our current
    for(int i = sl->level; i >= 0; i--){
        while(curr->next[i] != NULL && compareFunc(data, curr->next[i]->data) > 0)
            curr = curr->next[i];
        update[i] = curr;
    }

    //getting into a element that is bigger or equal to our data
    curr = curr->next[0];
    //if it is equal it doesn't add it to our list
    if(curr == NULL || compareFunc(data, curr->data) != 0){
        //creating and initializing nodes
        int newLevel = randomLevel(sl->maxLevel);
        node_t *new = create_node(data, newLevel);

        //setting the new highest level if our node has the biggest level in the list
        if(newLevel > sl->level){
            for(int i = sl->level+1; i <= newLevel; i++)
                update[i] = sl->head;
            sl->level = newLevel;
        }

        //linking our new nodes to the list
        for(int i = 0; i <= newLevel; i++){
            new->next[i] = update[i]->next[i];
            update[i]->next[i] = new;
        }

        free(update);
        return 1;
    }

    free(update);
    freeFunc(data);
    return 0;
}

/**
 * @brief checks if a element is in list, if it is it returns said element
 * 
 * @param sl skip list struct
 * @param data data to be searched
 * @param compareFunc function to compare data elements
 * @param freeFunc function to free data
 * @return node_t* skip list node
 */
node_t *is_in_list(skip_t *sl, void *data, int (*compareFunc) (), void (*freeFunc) ()){
    node_t *curr = sl->head;
    //searching for a element in the lowest level that has the next element bigger than our data
    for(int i = sl->level; i >= 0; i--){
        while(curr->next[i] != NULL && compareFunc(data, curr->next[i]->data) > 0)
            curr = curr->next[i];
    }

    curr = curr->next[0];
    if(curr != NULL && compareFunc(data, curr->data) == 0)
        return curr;
    else{
        return NULL;
        freeFunc(data);
    }
}

/**
 * @brief changes a data in a list
 * 
 * @param sl skip list struct
 * @param data data to be changed
 * @param compareFunc function to compare data elements
 * @param freeFunc function to free data
 * @return int returns if that data is in the list
 */
int change_data_in_list(skip_t *sl, void *data, int (*compareFunc) (), void (*freeFunc) ()){
    node_t *change = is_in_list(sl, data, compareFunc, freeFunc);

    if(change == NULL){
        freeFunc(data);
        return 0;
    }

    void *toFree = change->data;
    change->data = data;
    freeFunc(toFree);
    return 1;
}

/**
 * @brief removes data from list
 * 
 * @param sl skip list struct
 * @param data data do be removed
 * @param compareFunc function to compare data elements
 * @param freeFunc function to free data
 * @return int returns if a data was successfully removed from list
 */
int remove_data_from_list(skip_t *sl, void *data, int (*compareFunc) (), void (*freeFunc) ()){
    node_t *curr = sl->head;
    node_t **update = (node_t **)malloc((sl->maxLevel + 1) * sizeof(node_t *));

    //initializing update variable
    for(int i = 0; i <= sl->maxLevel; i++)
        update[i] = NULL;
    
    //running update through elements and getting those that have the next pointer to a data bigger than our current
    for(int i = sl->level; i >= 0; i--){
        while(curr->next[i] != NULL && compareFunc(data, curr->next[i]->data) > 0)
            curr = curr->next[i];
        update[i] = curr;
    }
    
    //getting into a element that is bigger or equal to our data
    curr = curr->next[0];
    //if it is equal it doesn't add it to our list
    if(curr != NULL && compareFunc(data, curr->data) == 0){
        //updates our list to not include our element(if its present)
        for(int i = 0; i <= sl->level; i++){
            if(update[i]->next[i] != curr)
                break;

            update[i]->next[i] = curr->next[i];
        }

        //reach lowest level and remove all nodes;
        while(sl->level > 0 && sl->head->next[sl->level] == NULL)
            sl->level--;

        freeFunc(data);
        freeFunc(curr->data);
        free(curr->next);
        free(curr);
        free(update);
        return 1;
    }

    free(update);
    freeFunc(data);
    return 0;
}

/**
 * @brief searches a element in the list and prints it
 * 
 * @param sl skip list struct
 * @param data data to be searched
 * @param compareFunc function to compare data elements
 * @param printFunc function to free data
 * @param freeFunc function to print data
 * @return int returns if said element can be found in the list
 */
int search_in_list(skip_t *sl, void *data, int (*compareFunc) (), void (*printFunc) (), void (*freeFunc) ()){
    node_t *search = is_in_list(sl, data, compareFunc, freeFunc);

    freeFunc(data);
    if(search == NULL){
        return 0;
    }

    printFunc(search->data);
    return 1;
}

/**
 * @brief print elements in a list
 * 
 * @param sl skip list struct
 * @param data data to be printed
 * @param compareFunc function to compare data elements
 * @param printFunc function to free data
 * @return int returns if those elements can be printed
 */
int print_list(skip_t *sl, void *data, int (*compareFunc) (), void (*printFunc) ()){
    node_t *curr = sl->head;
    //progress through the list until we find a element in the last level that has the next element
    //be bigger than data
    for(int i = sl->level; i >= 0; i--){
        while(curr->next[i] != NULL && compareFunc(data, curr->next[i]->data) > 0)
            curr = curr->next[i];
    }

    curr = curr->next[0];
    //progress through the last level until we find something we don't want to print
    if(curr != NULL && compareFunc(data, curr->data) == 0){
        while(curr != NULL && compareFunc(data, curr->data) == 0){
            printFunc(curr->data);
            curr = curr->next[0];
        }

        return 1;
    }

    return 0;
}

/**
 * @brief deallocates all elements in a skip list
 * 
 * @param sl skip list struct
 * @param freeFunc function to print data
 */
void destroy_list(skip_t *sl, void (*freeFunc) ()){
    node_t *aux, *curr;
    //freeing all elements in the last level
    curr = sl->head->next[0];
    while(curr != NULL){
        aux = curr;
        curr = curr->next[0];
        freeFunc(aux->data);
        free(aux->next);
        free(aux);
    }
    free(sl->head->next);
    free(sl->head);
    free(sl);
}