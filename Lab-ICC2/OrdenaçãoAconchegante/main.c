/*
 * Subject: Introduction to Computer Science 2 Laboratory
 *
 * Title: Rotating list
 * 
 * Functionality: This program is a implementation of a sorting algorithm.
 * 
 * Name: Murillo Moraes Martins
 * 
 * USP number: 12701599
 *
 * Date of the last modification: 01/10/2021
*/

#include <stdio.h>
#include <stdlib.h>

void sortingAlgorithm(float *vec, int *indexes, int size);
char *readWord(char *text);

int main(int argc, char *argv[]){
    //getting the amount of shells we will need to sort
    int shellAmount;
    scanf("%d", &shellAmount);

    //arrays needed during program execution
    float *shellDiameters = (float *)malloc(shellAmount * sizeof(float));
    char **shellColors = (char **)malloc(shellAmount * sizeof(char *));
    char **shellTextures = (char **)malloc(shellAmount * sizeof(char *));
    //this array is storing the original indexes so we will be able to print this in order after the sort
    int *indexes = (int *)malloc(shellAmount * sizeof(int));

    //storing user input
    for(int i = 0; i < shellAmount; i++){
        scanf(" %f ", &shellDiameters[i]);
        shellColors[i] = readWord(shellColors[i]);
        shellTextures[i] = readWord(shellTextures[i]);
        indexes[i] = i;
    }

    //sorting
    sortingAlgorithm(shellDiameters, indexes, shellAmount);

    //printing
    for(int i = 0; i < shellAmount; i++){
        printf("%.3f %s %s\n", shellDiameters[i], shellColors[indexes[i]], shellTextures[indexes[i]]);
    }

    //deallocating dinamic memory
    for(int i = 0; i < shellAmount; i++){
        free(shellColors[i]);
        free(shellTextures[i]);
    }
    free(shellDiameters);
    free(indexes);

    //return 0
    return 0;
}

/**
 * @brief sorting algorithm that will sort a array in ascending order
 * 
 * @param vec array to be sorted
 * @param indexes index array
 * @param size array size
 */
void sortingAlgorithm(float *vec, int *indexes, int size){
    //each iteration we divide the array into n/2 (virtual)subarrays until we reach n/2 = 1
    for(int div = size/2; div >= 1; div /= 2){
        //iterating between each subarray
        for(int i = 0; i < div; i++){
            
            //variables used for the sort
            float key;
            int keyIndex;
            int j, k;

            //here we make a insertion sort in each subarray
            for(j = 1; j < (size/div) + (size%2); j++){
                //checking if we are in the array's boundaries so we don't acess invalid memory
                if(j*(div) + i < size){
                    //creating keys
                    key = vec[j*(div) + i];
                    keyIndex = indexes[j*(div) + i];

                    k = (j-1)*(div) + i;
                    while(k >= i && vec[k] > key){
                        //sorting elements bigger than our key
                        vec[k + div] = vec[k];
                        indexes[k + div] = indexes[k];
                        k = k-div;
                    }

                    //inserting key in its sorted position in the subarray
                    vec[k+div] = key;
                    indexes[k+div] = keyIndex;
                }
            }
        }
    }
}

/**
 * @brief reads a word from stdin
 * 
 * @param text variable that will store the string
 * @return int returns a 1 if a \n is found, otherwise, returns a 0
 */
char *readWord(char *text){
    //initializing variables
    char readout;
    int textSize = 0;
    text = NULL;

    //reads from stdin until it finds a '\n', '\r' or a space (and allocates the necessary memory)
    do{
        readout = getchar();
        text = (char *)realloc(text, (textSize+1)*sizeof(char));
        text[textSize] = readout;
        textSize++;
    }while(readout != '\n' && readout != ' ' && readout != '\r');

    //if the last character is a '\r', it reads again
    //this is done in case it finds a '\r\n'
    if(readout == '\r')
        readout = getchar();

    //[textSize-1] is used because textSize is incremented in the previous while
    text[textSize-1] = '\0';

    return text;
}