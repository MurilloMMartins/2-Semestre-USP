#include <stdlib.h>
#include <string.h>
#include "frequency.h"

#define TRUE 1
#define FALSE 0

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