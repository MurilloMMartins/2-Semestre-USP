#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treap.h"

int readWord(char **text);

int main(int argc, char *argv[]){

    //getting the amount of commands
    int commandAmount;
    scanf(" %d", &commandAmount);
    scanf("%*[\r\n]s");

    treap_t *tree = create_treap();

    for(int i = 0; i < commandAmount; i++){
        char *command;
        readWord(&command);

        //deciding which command to execute
        if(strcmp(command, "insercao") == 0){
            int key, priority;
            scanf("%d %d", &key, &priority);

            if(!insert_treap(tree, key, priority))
                printf("Elemento ja existente\n");
            scanf("%*[\r\n]s");
        }
        else if(strcmp(command, "remocao") == 0){
            int key;
            scanf("%d", &key);

            if(!remove_treap(tree, key))
                printf("Chave nao localizada\n");
            scanf("%*[\r\n]s");
        }
        else if(strcmp(command, "buscar") == 0){
            int key;
            scanf("%d", &key);

            printf("%d\n", search_treap(tree->root, key));

            //checking if we have a ' ' after our command
            char trash = getchar();
            if(trash != ' ')
                ungetc(trash, stdin);
            scanf("%*[\r\n]s");
        }
        else if(strcmp(command, "impressao") == 0){
            char *mode;
            readWord(&mode);

            if(strcmp(mode, "ordem") == 0)
                print_treap(tree, 0);
            else if(strcmp(mode, "posordem") == 0)
                print_treap(tree, 1);
            else if(strcmp(mode, "preordem") == 0)
                print_treap(tree, 2);
            else if(strcmp(mode, "largura") == 0)
                print_treap(tree, 3);

            free(mode);
        }

        free(command);
    }

    destroy_treap(tree);
    
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