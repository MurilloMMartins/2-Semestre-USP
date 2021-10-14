/*
 * Subject: Algorithms and Data Structures 1 
 *
 * Title: Most frequent words
 * 
 * Functionality: The program stores a string (typed by the user) and counts the most frequent words
 * in said string, after that it prints the N most frequent stringd (the number N is a integer that 
 * is typed by the user). The program finishes its execution after a EOF. It utilizes a ADT (abstract
 * data type), it this case it uses the queue data type (which can be found in the "sources" folder, its
 * .h can be found in the "includes" folder)
 * 
 * Name: Murillo Moraes Martins
 * 
 * USP number: 12701599
 *
 * Date of the last modification: 17/09/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "frequency.h"

#define TRUE 1
#define FALSE 0

int readWord(char **text);
void fillQueue(queue_t *q);

int main(){
    //variable that controls whether or not we reached EOF
    char control;
    do{
        //creating queue
        queue_t *text;
        text = create();
        //reading from stdin and storing contents in the queue
        fillQueue(text);

        //creating a counter struct that will store the unique words and the amount of times they appear in a string
        counter_t wordCounter;
        initializeStruct(&wordCounter);
    
        //emptying the queue and adding the unique words/ number of appearances in the counter struct
        while(isEmpty(text) != TRUE){
            char *word;
            dequeue(text, &word);
            if(isUniqueWord(&wordCounter, word) == TRUE)
                    addUniqueWord(&wordCounter, word);
            free(word);
        }

        //initializing a index Array
        //this will be used to store the indexes of the words while sorting
        int *indexesArray;
        indexesArray = (int *)malloc(wordCounter.size * sizeof(int));
        for(int i = 0; i < wordCounter.size; i++){
            indexesArray[i] = i;
        }

        sortNumbers(indexesArray, wordCounter.amounts, wordCounter.size);
        sortWords(&wordCounter, indexesArray);

        //storing amount of unique words that will need to be show in the screen
        int amountOfWords;
        scanf(" %d", &amountOfWords);

        if(amountOfWords >= wordCounter.size)
            amountOfWords = wordCounter.size;
    
        for(int i = wordCounter.size-1; i >= wordCounter.size - amountOfWords; i--){
            printf("%s %d\n", wordCounter.words[indexesArray[i]], wordCounter.amounts[i]);
        }

        //freeing all the dinamically alocated variables
        free(indexesArray);
        destroyStruct(&wordCounter);
        destroy(text);

        //this section controls whether we have reached a end of file or a \r\n
        control = getchar();
        if(control == '\r'){
            control = getchar();
            control = getchar();
        }
        if(control != EOF){
            printf("\n");
            ungetc(control, stdin);
        }
            
    }while(control != EOF);
    
    //return ...something i guess, can't remember
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