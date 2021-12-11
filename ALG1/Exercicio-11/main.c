#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"

int readWord(char **text);

int main(int argc, char *argv[]){

    BST_t *tree = create_bst();

    int hasEnded = 0;
    while(hasEnded == 0){
        char *command;
        hasEnded = readWord(&command);

        //deciding the command
        if(strcmp(command, "insercao") == 0){
            int value;
            scanf(" %d", &value);

            insert_bst(&tree->root, value);

            //checking if we find a EOF
            char isEOF = getchar();
            if(isEOF == EOF)
                hasEnded = 1;
            else{
                ungetc(isEOF, stdin);
                scanf("%*[\r\n]s");
            }
        }
        else if(strcmp(command, "impressao") == 0){
            char *order;
            hasEnded = readWord(&order);

            //printing in the right order
            if(strcmp(order, "pre-ordem") == 0)
                print_bst(tree->root, -1);
            else if(strcmp(order, "em-ordem") == 0)
                print_bst(tree->root, 0);
            else if(strcmp(order, "pos-ordem") == 0)
                print_bst(tree->root, 1);

            free(order);
        }
        free(command);
        
    }

    destroy_bst(tree->root);
    free(tree);

    return 0;
}

/**
 * @brief reads a word from stdin
 * 
 * @param text variable that will store the string
 * @return int returns a 1 if a EOF is found, otherwise, returns a 0
 */
int readWord(char **text){
    //initializing variables
    char readout;
    int textSize = 0;
    (*text) = NULL;

    //reads from stdin until it finds a '\n', '\r', EOF or a space (and allocates the necessary memory)
    do{
        readout = getchar();
        *text = (char *)realloc(*text, (textSize+1)*sizeof(char));
        (*text)[textSize] = readout;
        textSize++;
    }while(readout != '\n' && readout != ' ' && readout != '\r' && readout != EOF);

    //if the last character is a '\r', it reads again
    //this is done in case it finds a '\r\n'
    if(readout == '\r')
        readout = getchar();

    //[textSize-1] is used because textSize is incremented in the previous while
    (*text)[textSize-1] = '\0';

    if(readout == EOF)
        return 1;
    return 0;
}