/*
 * Subject: Algorithms and Data Structures 1 
 *
 * Title: Substitute Str
 * 
 * Functionality: This program has the functionality of substituting a substring inside a given string.
 * For example, if we have the string "Exemple", we can instruct the program to substitute the substring 
 * "em" for "am", then it'll print "Example", resulting in a correction of the word.
 * 
 * Name: Murillo Moraes Martins
 * 
 * USP number: 12701599
 *
 * Date of the last modification: 19/09/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0

int readWord(char **text);
int readLine(char **text);
void fillQueue(queue_t *q);
void printCorrectedText(queue_t *q, char *mistake, char *correction);
void printCorrectedWord(char *errorLocation, char *word, char *mistake, char *correction);


int main(){
    //controls whether we've reached EOF or not
    int control;
    do{
        //creating and filling queue
        queue_t *text;
        text = create();
        fillQueue(text);

        //reading lines
        char *mistake;
        readLine(&mistake);

        char *correction;
        control = readLine(&correction);

        //correcting and printing texts
        printCorrectedText(text, mistake, correction);

        //freeing variables allocated
        free(mistake);
        free(correction);
        destroy(text);

        //printing \n while we don't reach EOF
        if(control != 1)
            printf("\n");

    }while(control != 1);
    
    //return 0, the best part of this whole code, if you don't agree you're wrong :)
    return 0;
}

/**
 * @brief reads a word from stdin
 * 
 * @param text variable that will store the string
 * @return int returns a 1 if a \n is found, otherwise, returns a 0
 */
int readWord(char **text){
    //initializing variables
    char readout;
    int textSize = 0;
    (*text) = NULL;

    //reads from stdin until it finds a '\n', '\r' or a space (and allocates the necessary memory)
    do{
        readout = getchar();
        *text = (char *)realloc(*text, (textSize+1)*sizeof(char));
        (*text)[textSize] = readout;
        textSize++;
    }while(readout != '\n' && readout != ' ' && readout != '\r');

    //if the last character is a '\r', it reads again
    //this is done in case it finds a '\r\n'
    if(readout == '\r')
        readout = getchar();

    //[textSize-1] is used because textSize is incremented in the previous while
    (*text)[textSize-1] = '\0';

    if(readout == '\n')
        return TRUE;
    return FALSE;
}

/**
 * @brief reads a line from the input stream
 * 
 * @param text variable that will hold the string
 * @return int returns 1 if it finds a EOF, 0 otherwise
 */
int readLine(char **text){
    //initializing variables
    char readout;
    int textSize = 0;
    (*text) = NULL;

    //reads from stdin until it finds a '\n', '\r' or EOF(and allocates the necessary memory)
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

    //returns 1 if it finds a EOF
    if(readout == EOF)
        return 1;
    return 0;
}

/**
 * @brief fills a queue with the words from a string typed by the user
 * 
 * @param q queue struct
 */
void fillQueue(queue_t *q){
    //control variable (will be TRUE if the function finds a \n)
    int hasFinished = FALSE;
    do{
        char *word;
        hasFinished = readWord(&word);
        enqueue(q, word);
        free(word);
    }while(hasFinished != TRUE);
}

/**
 * @brief prints the original text with the corrections requested by the user
 * 
 * @param q queue struct
 * @param mistake string that contains the mistake that will be corrected
 * @param correction string that contains the correction
 */
void printCorrectedText(queue_t *q, char *mistake, char *correction){
    while(isEmpty(q) != 1){
        char *word = NULL;
        dequeue(q, &word);

        //checking if the error is present in the current word
        char *hasError = NULL;
        hasError = strstr(word, mistake);
        if(hasError != NULL){
            printCorrectedWord(hasError, word, mistake, correction);
        }
        else{
            printf("%s", word);
        }

        //prints spaces unless it's the last word in the string
        if(isEmpty(q) != 1){
            printf(" ");
        }

        free(word);
    }
}

/**
 * @brief corrects the mistake present in a word and prints it
 * 
 * @param afterMistake pointer to the start of the mistake
 * @param word entire word
 * @param mistake mistake string
 * @param correction correction string
 */
void printCorrectedWord(char *afterMistake, char *word, char *mistake, char *correction){
    /*
    * to explain what this function does, presume we have the word "Exemple", and we want to
    * substitute the "em" for "am", then we have the following data going into the function:
    *               printCorrectedWord("emple", "Exemple", "em", "am")
    */

    //Here we get the sizes that will be used to find the exact place where the mistake is located
    int wordSize = strlen(word);
    int afterMistakeSize = strlen(afterMistake);
    int mistakeSize = strlen(mistake);

    /*
    * here we get the following locations:
    * mistakeStart:
    *     |
    *     V
    *   Exemple
    * 
    * mistakeEnd:
    *       |
    *       V
    *   Exemple
    */
    int mistakeStart = wordSize - afterMistakeSize;
    int mistakeEnd = afterMistakeSize - (afterMistakeSize - mistakeSize);

    /*
    * Here we print the following things:
    * 1: "Ex"
    * 2: "am"
    * 3: "ple"
    */
    for(int i = 0; i < mistakeStart; i++){
        printf("%c", word[i]);
    }
    printf("%s", correction);
    for(int i = mistakeEnd; i < afterMistakeSize; i++){
        printf("%c", afterMistake[i]);
    }
}