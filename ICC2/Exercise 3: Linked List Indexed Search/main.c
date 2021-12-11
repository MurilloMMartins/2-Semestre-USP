/**
 * @file main.c
 * @author Murillo Moraes Martins (12701599)
 * @brief This program implements a Linked List with Indexed Search, this means when we try to search
 * a element in our linked list, instead of going through all the elements in our list to find one, we
 * use a index vector that leads us to a predetermined point in our list depending on a key (in this case
 * the keys are the letters of the alphabet, so, when we search, we start at the first element with the
 * same initial letter and progress through that).
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

int readLine(char **text, FILE *file);
void readFile(FILE *f, list_t *l);

int main(int argc, char *argv[]){

    //initializing structures
    FILE *file = NULL;
    list_t *list = create_list();
    index_vector_t *indexVector = NULL;

    //this variables checks if our index vector was updated after new items have been inserted into the list
    int isUpdated = 0;

    int command;
    do{
        scanf(" %d", &command);

        //declaring auxiliary variables
        char *fileName;
        char *word;
        int path;

        switch(command){
            case 1:
                //avoiding \r\n into our string
                scanf("%*[\r\n]s");
                //opening file and saving it's contents to the list
                readLine(&fileName, stdin);
                file = fopen(fileName, "r");
                readFile(file, list);

                //freeing variables used
                fclose(file);
                free(fileName);

                print_list_head(list);
                isUpdated = 0;
                break;
            case 2:
                //destroying index vector if it's not NULL
                if(indexVector != NULL)
                    destroy_index_vector(indexVector);
                
                //creating index vector based on current list
                indexVector = create_index_vector(list);
                print_index_size(indexVector);
                isUpdated = 1;
                break;
            case 3:
                //avoiding \r\n into our string
                scanf("%*[\r\n]s");
                readLine(&word, stdin);

                //checking if our index vector is updated
                if(isUpdated){
                    path = search_list(indexVector, word);
                    //checking id word exists in our list
                    if(path == -1)
                        printf("Palavra nao existe na lista.\n");
                    else
                        printf("%d\n", path);
                }
                else{
                    printf("Vetor de indices nao atualizado.\n");
                }
                free(word);
                break;
            default:
                break;
        }
    }while(command != 0);

    //deallocating memory
    destroy_index_vector(indexVector);
    destroy_list(list);

    return 0;
}

/**
 * @brief reads a word from stdin
 * 
 * @param text variable that will store the string
 * @return int returns a 1 if a EOF is found, otherwise, returns a 0
 */
int readLine(char **text, FILE *file){
    //initializing variables
    char readout;
    int textSize = 0;
    (*text) = NULL;

    //reads from stdin until it finds a '\n', '\r' or a EOF (and allocates the necessary memory)
    do{
        readout = getc(file);
        *text = (char *)realloc(*text, (textSize+1)*sizeof(char));
        (*text)[textSize] = readout;
        textSize++;
    }while(readout != '\n' && readout != '\r' && readout != EOF);

    //if the last character is a '\r', it reads again
    //this is done in case it finds a '\r\n'
    if(readout == '\r')
        readout = getc(file);

    //[textSize-1] is used because textSize is incremented in the previous while
    (*text)[textSize-1] = '\0';

    if(readout == EOF)
        return 1;
    return 0;
}

void readFile(FILE *f, list_t *l){
    int hasEnded = 0;
    do{
        char *word;
        hasEnded = readLine(&word, f);
        insert_in_list(l, word);
        free(word);
    }while(hasEnded != 1);
}