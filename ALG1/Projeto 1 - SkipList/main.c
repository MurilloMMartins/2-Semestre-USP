/**
 * @file main.c
 * @author Murillo moraes Martins (12701599)
 * @brief this program implements a dictionary using the skip list data structure
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skip_list.h"

#define MAX_LEVEL 20

typedef struct dictionary{
    char *word;
    char *definition;
}dict_t;

int readWord(char **text);
int readLine(char **text);

int compareWords(dict_t *d1, dict_t *d2);
void freeDict(dict_t *d);
void printDict(dict_t *d);
int compareFirstLetter(dict_t *d1, dict_t *d2);

int main(int argc, char *argv[]){
    
    int control = 0;
    skip_t *list = create_list(MAX_LEVEL);
    //control is onl != 0 if we reach a EOF
    while(control == 0){
        char *command;
        control = readWord(&command);
        
        //comparing the commands
        if(strcmp(command, "insercao") == 0){
            //reading necessary input
            dict_t *newElem = (dict_t *)malloc(sizeof(dict_t));
            readWord(&newElem->word);
            control = readLine(&newElem->definition);

            if(!insert_in_list(list, newElem, compareWords, freeDict))
                printf("OPERACAO INVALIDA\n");
        }
        else if(strcmp(command, "alteracao") == 0){
            //reading necessary input
            dict_t *changedElem = (dict_t *)malloc(sizeof(dict_t));
            readWord(&changedElem->word);
            control = readLine(&changedElem->definition);

            if(!change_data_in_list(list, changedElem, compareWords, freeDict))
                printf("OPERACAO INVALIDA\n");
        }
        else if(strcmp(command, "remocao") == 0){
            //reading necessary input
            dict_t *removedElem = (dict_t *)malloc(sizeof(dict_t));
            control = readLine(&removedElem->word);
            removedElem->definition = NULL;

            if(!remove_data_from_list(list, removedElem, compareWords, freeDict))
                printf("OPERACAO INVALIDA\n");
        }
        else if(strcmp(command, "busca") == 0){
            //reading necessary input
            dict_t *searchElem = (dict_t *)malloc(sizeof(dict_t));
            control = readLine(&searchElem->word);
            searchElem->definition = NULL;

            if(!search_in_list(list, searchElem, compareWords, printDict, freeDict))
                printf("OPERACAO INVALIDA\n");
        }
        else if(strcmp(command, "impressao") == 0){
            //reading necessary input
            dict_t *printElem = (dict_t *)malloc(sizeof(dict_t));
            control = readLine(&printElem->word);
            printElem->definition = NULL;

            if(!print_list(list, printElem, compareFirstLetter, printDict))
                printf("NAO HA PALAVRAS INICIADAS POR %s\n", printElem->word);
            
            freeDict(printElem);
        }
        free(command);
    }

    destroy_list(list, freeDict);

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

/**
 * @brief reads a word from stdin
 * 
 * @param text variable that will store the string
 * @return int returns a 1 if a EOF is found, otherwise, returns a 0
 */
int readLine(char **text){
    //initializing variables
    char readout;
    int textSize = 0;
    (*text) = NULL;

    //reads from stdin until it finds a '\n', '\r' or a EOF (and allocates the necessary memory)
    do{
        readout = getchar();
        *text = (char *)realloc(*text, (textSize+1)*sizeof(char));
        (*text)[textSize] = readout;
        textSize++;
    }while(readout != '\n' && readout != '\r' && readout != EOF);

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

/**
 * @brief compares two words in a dict
 * 
 * @param d1 dict struct
 * @param d2 dict struct
 * @return int state between two words
 */
int compareWords(dict_t *d1, dict_t *d2){
    return strcmp(d1->word, d2->word);
}

/**
 * @brief frees a dict struct
 * 
 * @param d dict struct
 */
void freeDict(dict_t *d){
    free(d->word);
    if(d->definition != NULL)
        free(d->definition);
    free(d);
}

/**
 * @brief prints a dict word and definition
 * 
 * @param d dict structure
 */
void printDict(dict_t *d){
    printf("%s %s\n", d->word, d->definition);
}

/**
 * @brief compares the first letters of two dict words
 * 
 * @param d1 dict struct
 * @param d2 dict struct
 * @return int the state between the letters
 */
int compareFirstLetter(dict_t *d1, dict_t *d2){
    if(d1->word[0] > d2->word[0])
        return 1;
    else if(d1->word[0] < d2->word[0])
        return -1;
    return 0;
}