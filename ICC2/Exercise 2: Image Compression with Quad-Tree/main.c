#include <stdio.h>
#include <stdlib.h>

typedef struct coordinates{
    int x;
    int y;
}coord_t;

typedef struct tree tree_t;

struct tree{
    int data;
    coord_t coord;
    int size;
    tree_t *children;
};

int **readMatrix(int sizeX, int sizeY);
tree_t initializeTree(int size);
void buildTree(tree_t *tree, int **mat);
int evaluateBranch(tree_t tree, int **mat);
void printTree(tree_t tree);
void freeTree(tree_t tree);

int main(int argc, char *argv[]){

    //reading matrix size from input
    int sizeX, sizeY;
    scanf("%d %d", &sizeX, &sizeY);

    //reading matrix
    int **matrix = readMatrix(sizeX, sizeY);

    tree_t tree = initializeTree(sizeX);
    //building and printing the tree
    buildTree(&tree, matrix);
    printTree(tree);
    printf("\n");

    //freeing allocated memory
    freeTree(tree);
    for(int i = 0; i < sizeY; i++){
        free(matrix[i]);
    }
    free(matrix);

    //returning 0
    return 0;
}

/**
 * @brief reads a matrix from stdin
 * 
 * @param sizeX x matrix size
 * @param sizeY y matrix size
 * @return int** matrix pointer
 */
int **readMatrix(int sizeX, int sizeY){
    int **mat = (int **)malloc(sizeY * sizeof(int *));
    for(int i = 0; i < sizeY; i++){
        mat[i] = (int *)malloc(sizeX * sizeof(int));
        for(int j = 0; j < sizeX; j++){
            scanf(" %d", &mat[i][j]);
        }
    }

    return mat;
}

/**
 * @brief initializes a tree struct
 * 
 * @param size matrix size
 * @return tree_t tree struct
 */
tree_t initializeTree(int size){
    tree_t tree;
    tree.data = -1;
    tree.coord.x = 0;
    tree.coord.y = 0;
    tree.size = size;
    tree.children = NULL;

    return tree;
}

/**
 * @brief recursive function that builds a tree based on the matrix's value
 * 
 * @param tree tree struct
 * @param mat matrix
 */
void buildTree(tree_t *tree, int **mat){
    //evaluating if the tree needs more branches
    tree->data = evaluateBranch(*tree, mat);

    if(tree->data == -1){
        //allocating children
        tree->children = (tree_t *)malloc(4 * sizeof(tree_t));

        //initializing children values
        for(int i = 0; i < 4; i++){
            tree->children[i].size = tree->size/2;
            //initializing coordinates
            tree->children[i].coord.x = i % 2 == 0? tree->coord.x : (tree->coord.x + tree->size/2);
            tree->children[i].coord.y = i < 2 ? tree->coord.y : (tree->coord.y + tree->size/2);
            tree->children[i].children = NULL;
            //recursive step
            buildTree(&tree->children[i], mat);
        }
    }
}

/**
 * @brief evaluates if we need to create more branches in our tree
 * 
 * @param tree tree struct
 * @param mat matrix data
 * @return int if its -1, more branches will be created, otherwise we return the data
 */
int evaluateBranch(tree_t tree, int **mat){
    //if every value in the submatrix is the same we return this key
    int key = mat[tree.coord.y][tree.coord.x];
    for(int i = 0; i < tree.size; i++){
        for(int j = 0; j < tree.size; j++){
            if(key != mat[tree.coord.y + i][tree.coord.x + j])
                return -1;
        }
    }

    return key;
}

/**
 * @brief prints the data in a tree struct
 * 
 * @param tree tree struct
 */
void printTree(tree_t tree){
    printf("%d ", tree.data);
    if(tree.data == -1){
        for(int i = 0; i < 4; i++){
            printTree(tree.children[i]);
        }
    }
}

/**
 * @brief frees all the children from the tree
 * 
 * @param tree tree struct
 */
void freeTree(tree_t tree){
    if(tree.data == -1){
        for(int i = 0; i < 4; i++){
            freeTree(tree.children[i]);
        }
    }
    free(tree.children);
}