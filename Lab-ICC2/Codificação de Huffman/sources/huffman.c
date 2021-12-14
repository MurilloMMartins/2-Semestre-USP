#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

//------------------------------------------------------------------------------------------------//
                                    //Huffman Tree Functions//
                                    //and Auxilary Functions//

typedef struct node node_t;
struct node{
    char symbol;
    int freq;
    node_t *left, *right;
};

typedef struct node_array{
    node_t **array;
    int size;
} n_array_t;

/**
 * @brief swaps the data of two nodes
 * 
 * @param n1 first node
 * @param n2 second node
 */
void swap_nodes(node_t **n1, node_t **n2){
    node_t *tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}

/**
 * @brief puts a element in a heap position where it's childen are bigger than or equal to it and it 
 * father is smaller than it's info
 * 
 * @param a node array structure
 * @param father father's index
 * @param size size of the node array
 */
void min_heapify(n_array_t *a, int father, int size) {
    //calculating the first son's position according to heap rule
	int son = father*2 + 1;

	if (son > size) return;

	if (a->array[son]->freq < a->array[father]->freq || (son+1 <= size && a->array[son+1]->freq < a->array[father]->freq) ) {
        //deciding which son is smaller to swap with the father's position
		if (son+1 <= size && a->array[son+1]->freq < a->array[son]->freq)
			son = son+1;

        swap_nodes(&(a->array[father]), &(a->array[son]));
		min_heapify(a, son, size);
	}
}

/**
 * @brief organizes a array based on the minheap rule
 * 
 * @param a 
 * @param size 
 */
void build_minheap(n_array_t *a, int size){
    int s = (int) size/2.0;

    //it's only necessary to min heapify half of the array to create a min heap
    for(int i = s; i >= 0; i--)
        min_heapify(a, i, size);
}

/**
 * @brief creates a array of tree nodes based on the letters, and their frequency, in a string
 * 
 * @param string string
 * @return n_array_t* node array
 */
n_array_t *create_frequency_nodes(char *string){

    //initializing the node array
    n_array_t *n = malloc(sizeof(n_array_t));
    n->array = NULL;
    n->size = 0;

    //iterating through the characters in the string
    for(int i = 0; i < strlen(string); i++){
        //variables that control's whether a character already exists in our array
        int incremented = 0;

        //iterating through array to see if the current character is already in it
        for(int j = 0; j < n->size; j++){
            //if it is we increment it's frequency
            if(n->array[j]->symbol == string[i]){
                n->array[j]->freq++;
                incremented = 1;
                break;
            }
        }

        //if it isn't we allocate a new space for it and initializes the node strucuture
        if(incremented == 0 || n->array == NULL){
            n->array = realloc(n->array, (++n->size) * sizeof(node_t *));
            n->array[n->size-1] = malloc(sizeof(node_t));
            n->array[n->size-1]->freq = 1;
            n->array[n->size-1]->symbol = string[i];
            n->array[n->size-1]->left = NULL;
            n->array[n->size-1]->right = NULL;
        }

    }

    //in the end we make the array into a min heap to facilitate further operations
    build_minheap(n, n->size-1);

    return n;
}
                                    
struct huffman_tree{
    node_t *root;
};

huff_t *create_huffman_tree(char *string){
    //creating the node array
    n_array_t *arr = create_frequency_nodes(string);

    int size = arr->size;
    //iterating through array building the tree
    while(size != 1){
        //swapping the first and last node and min heapifying without the last element(essencially removing it from the heap)
        swap_nodes(&arr->array[0], &arr->array[size-1]);
        min_heapify(arr, 0, size-2);

        //allocating new node and assigning the two smallest nodes on the list as it's childen
        node_t *new = malloc(sizeof(node_t));
        //this serves as a "sentinel" to our tree
        new->symbol = '\0';
        new->freq = arr->array[0]->freq + arr->array[size-1]->freq;
        new->right = arr->array[0];
        new->left = arr->array[size-1];

        //putting the new node in the start of the array
        /* we don't lose the reference to the element that was previously there because it becomes 
        one of this node's children */
        arr->array[0] = new;
        size--;
        min_heapify(arr, 0, size-1);
    }

    //allocating the huffman structure and assigning its root
    huff_t *t = malloc(sizeof(huff_t));
    t->root = arr->array[0];

    //freeing memory used to build the tree
    free(arr->array);
    free(arr);

    return t;
}

/**
 * @brief recursivelly frees all memory from a huffman tre
 * 
 * @param root tree's root
 */
void destroy_tree(node_t *root){
    if(root == NULL)
        return;

    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

void destroy_huffman_tree(huff_t *tree){
    destroy_tree(tree->root);
    free(tree);
}

//------------------------------------------------------------------------------------------------//
                                    //Compression Map Functions//
                                    //and Auxilary Functions//

typedef struct compress{
    char symbol;
    char *encoding;
}comp_t;

struct compression_map{
    comp_t **array;
    int size;
};

/**
 * @brief builds a compression map based on a huffman tree
 * 
 * @param curr current node of the tree
 * @param map map structure
 * @param encoding string that will contain the encoding information
 * @param depth depth of the tree we are at
 */
void compress(node_t *curr, map_t *map, char **encoding, int depth){
    //allocating a new character to the encoding string
    *encoding = realloc(*encoding, depth * sizeof(char));
    
    //checking if we are at a leaf node
    if(curr->left == NULL && curr->right == NULL){
        //if we are, allocate a new element to the map compression map and fill it's data
        map->size++;
        map->array = realloc(map->array, map->size * sizeof(comp_t *));
        map->array[map->size-1] = malloc(sizeof(comp_t));
        map->array[map->size-1]->symbol = curr->symbol;
        map->array[map->size-1]->encoding = malloc(depth * sizeof(char));
        
        (*encoding)[depth-1] = '\0';
        //here we copy the current encoding string to our map
        strcpy(map->array[map->size-1]->encoding, *encoding);
        return;
    }

    //adding a one to the end if we are going to the right
    (*encoding)[depth-1] = '1';
    compress(curr->right, map, encoding, depth+1);

    //substituting the last element to a 0 if we are going to the left
    (*encoding)[depth-1] = '0';
    compress(curr->left, map, encoding, depth+1);

    //substituting the last element o a \0 if we have visited all nodes below our current
    (*encoding)[depth-1] = '\0';
}

map_t *create_compression_map(huff_t *tree){
    //initializing encoding string
    char *encoding = malloc(sizeof(char));
    //initializing the map structure
    map_t *map = malloc(sizeof(map_t));
    map->array = NULL;
    map->size = 0;

    //building the map strucutre
    compress(tree->root, map, &encoding, 1);
    free(encoding);

    return map;
}

void destroy_map(map_t *map){
    for(int i = 0; i < map->size; i++){
        free(map->array[i]->encoding);
        free(map->array[i]);
    }
    free(map->array);
    free(map);
}

void print_map(map_t *map){
    printf("character | encoding\n");
    for(int i = 0; i < map->size; i++)
        printf("    %c     | %s\n", map->array[i]->symbol, map->array[i]->encoding);
}

//------------------------------------------------------------------------------------------------//
                            //Compression and Decompression Functions//
                                    //and Auxilary Functions//

char *compress_string(map_t *map, char *string){
    //initializing our compressed string and it's size
    char *comp = malloc(sizeof(char));
    int size = 1;
    //iterating through the original string
    for(int i = 0; i < strlen(string); i++){
        //iterating through the compression map
        for(int j = 0; j < map->size; j++){
            //once we find the element in the map we add the encoding from the map to our compressed string
            if(map->array[j]->symbol == string[i]){
                comp[size-1] = '\0';
                size += strlen(map->array[j]->encoding);
                comp = realloc(comp, size * sizeof(char));
                
                strcat(comp, map->array[j]->encoding);
                break;
            }
        }
    }

    //adding \0 to the end
    comp = realloc(comp, (size+1) * sizeof(char));
    comp[size-1] = '\0';

    return comp;
}

char *decompress_string(huff_t *tree, char *string){
    //initializing the decompressed string and it's size
    char *decomp = NULL;
    int size = 0;

    int currChar = 0;
    //iterating through the compressed string
    while(currChar < strlen(string)){
        node_t *curr = tree->root;
        //iterate through the tree until we find a leaf node
        while(curr->left != NULL && curr->right != NULL){
            if(string[currChar] == '0')
                curr = curr->left;
            else if(string[currChar] == '1')
                curr = curr->right;
            currChar++;
        }

        //add the contents of that node to our decompressed string
        size++;
        decomp = realloc(decomp, size * sizeof(char));
        decomp[size-1] = curr->symbol;
    }

    //adding \0 to the end
    decomp = realloc(decomp, (size+1) * sizeof(char));
    decomp[size] = '\0';

    return decomp;
}

double calculate_compression_rate(char *orig, char *comp){
    return (strlen(comp)) / ((double) strlen(orig)*8);
}