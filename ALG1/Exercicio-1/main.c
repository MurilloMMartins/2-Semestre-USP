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

#define TRUE 1
#define FALSE 0

typedef struct counter{
    char **words;
    int *amounts;
    int size;
}counter_t;

int readWord(char **text);
void fillQueue(queue_t *q);
int isUniqueWord(counter_t *counter, char *word);
void initializeStruct(counter_t *counter);
void addUniqueWord(counter_t *counter, char *word);
void destroyStruct(counter_t *counter);
void sortNumbers(int *indexesArray, int *amountsArray, int size);
void sortWords(counter_t *counter, int *amountsArray);
int isWordBiggerThan(char *word1, char *word2);


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

/**
 * @brief returns if a word is unique in a array
 * 
 * @param counter 
 * @param word 
 * @return int 
 */
int isUniqueWord(counter_t *counter, char *word){
    //initializing the first word encountered
    if(counter->size == 0)
        return TRUE;

    //searching through the array
    for(int i = 0; i < counter->size; i++){
        if(strcmp(counter->words[i], word) == 0){
            counter->amounts[i]++;
            return FALSE;
        }
    }

    return TRUE;
}

/**
 * @brief initializes the counter struct
 * 
 * @param counter counter_t pointer
 */
void initializeStruct(counter_t *counter){
    counter->words = NULL;
    counter->amounts = NULL;
    counter->size = 0;
}

/**
 * @brief adds a unique word into a given array
 * 
 * @param counter counter struct which will contain the array
 * @param word word to be added
 */
void addUniqueWord(counter_t *counter, char *word){
    //incrementing the amount of words in that array
    counter->size++;

    //allocating memory for the string array
    counter->words = (char **)realloc(counter->words, counter->size * sizeof(char *));
    //allocating memory for the string
    int wordSize = strlen(word) + 1;
    counter->words[counter->size-1] = (char *)malloc(wordSize * sizeof(char));
    strcpy(counter->words[counter->size-1], word);

    //allocates a new space to the int array
    counter->amounts = (int *)realloc(counter->amounts, counter->size * sizeof(int));
    counter->amounts[counter->size-1] = 1;
    
}

/**
 * @brief free's the elements from the counter struct
 * 
 * @param counter 
 */
void destroyStruct(counter_t *counter){
    for(int i = 0; i < counter->size; i++){
        free(counter->words[i]);
    }
    free(counter->words);
    free(counter->amounts);
}

/**
 * @brief sorts the numbers from the amountArray (insertion sort used)
 * 
 * @param indexesArray array of indexes
 * @param amountsArray array of the amount of times the words have appeared
 * @param size size of both arrays
 */
void sortNumbers(int *indexesArray, int *amountsArray, int size){
    for(int i = 1; i < size; i++){
        int key = amountsArray[i];
        int index = indexesArray[i];
        int j = i-1;
        while(j >= 0 && amountsArray[j] > key){
            amountsArray[j+1] = amountsArray[j];
            indexesArray[j+1] = indexesArray[j];
            j--;
        }
        amountsArray[j+1] = key;
        indexesArray[j+1] = index;
        
    }
}

/**
 * @brief sorts the words in alphabetical order (bubble sort used, i guess)
 * 
 * @param counter counter struct
 * @param indexesArray array of indexes
 */
void sortWords(counter_t *counter, int *indexesArray){
    for(int i = 0; i < counter->size; i++){
        for(int j = 0; j < counter->size; j++){
            if(counter->amounts[i] == counter->amounts[j]){
                //checks if the chars in a word(that have the same occurence in the string) are bigger than another
                //if a word is "bigger" than another, than it is alphabetically smaller than another
                if(isWordBiggerThan(counter->words[indexesArray[i]], counter->words[indexesArray[j]]) == TRUE){
                    //swapping array values with temporary variables
                    int tempIndexes = indexesArray[i];
                    indexesArray[i] = indexesArray[j];
                    indexesArray[j] = tempIndexes;

                    int tempAmounts = counter->amounts[i];
                    counter->amounts[i] = counter->amounts[j];
                    counter->amounts[j] = tempAmounts;
                }
            }
        }
    }
}

/**
 * @brief checks if the characthers of a word are bigger than other
 * 
 * @param word1 word which will be compared
 * @param word2 word which will be compared
 * @return int returns 1 if word1 > word2, 0 otherwise
 */
int isWordBiggerThan(char *word1, char *word2){
    //gets the size of both words
    //this is needed to prevent the function from acessing invalid indexes
    int size1 = strlen(word1);
    int size2 = strlen(word2);
    
    //checking which string is bigger
    if(size1 >= size2){
        for(int i = 0; i < size2; i++){
            if(word1[i] != word2[i]){
                //the (unisgned char) cast is necessary because of special charactes (i.e.: 'é', 'á' and others)
                if((unsigned char)word1[i] > (unsigned char)word2[i])
                    return TRUE;
                return FALSE;
            }
        }
    }
    else if(size2 > size1){
        for(int i = 0; i < size1; i++){
            if(word1[i] != word2[i]){
                if((unsigned char)word1[i] > (unsigned char)word2[i])
                    return TRUE;
                return FALSE;
            }
        }
    }

    //error return
    return -1;
}