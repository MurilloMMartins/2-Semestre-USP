/**
 * @file main.c
 * @author Murillo Moraes Martins (NºUSP 12701599)
 * @brief Program that compresses a audio file, the user needs to input the name of the .wav file
 * and the amount of samples that will remain in the compressed file. This program will print the 
 * amount of samples (first line), the amount of coeficients that are less than or equal to zero 
 * before the Fourier Transform, and the sorted sequence of the N coeficients that will be maintained 
 * after the compression.
 * @version 0.1
 * @date 2021-10-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "wave.h"

/**
 * @brief coeficient struct, contains a data array(complex number array) and a index array
 * 
 */
typedef struct coeficients{
    double complex *data;
    int *indexes;
}coeficients_t;

char *readLine(char *text);
void printNegativeComplex(double complex *coef, int length);
int *initializeIndexes(int length);
double magnitude(double complex number);
void insertionSort(coeficients_t *coef, int size);

int main(int argc, char *argv[]){
    //reading the user's input
    char *fileName = NULL;
    fileName = readLine(fileName);
    int coefAmount;
    scanf(" %d", &coefAmount);

    //reading data from the .wav file
    int sampleAmount;
    unsigned char *audioData = read_wav_data(fileName, &sampleAmount);
    printf("%d\n", sampleAmount);

    //perforing the Discrete Fourier Transform
    coeficients_t coef;
    coef.data = DFT(audioData, sampleAmount);
    coef.indexes = initializeIndexes(sampleAmount);
    printNegativeComplex(coef.data, sampleAmount);

    //sorting
    insertionSort(&coef, sampleAmount);

    //printing desired coeficients
    // for(int i = 0; i < coefAmount; i++){
    //     printf("%d\n", (int)magnitude(coef.data[coef.indexes[i]]));
    // }

    //zeroing undesired coeficients
    for(int i = coefAmount; i < sampleAmount; i++){
        coef.data[coef.indexes[i]] = 0;
    }

    //saving compressed .wav file
    unsigned char *newAudioData = IFT(coef.data, sampleAmount);
    save_wav_data(fileName, newAudioData, sampleAmount);

    //deallocating memory
    free(newAudioData);
    free(fileName);
    free(audioData);
    free(coef.data);
    free(coef.indexes);

    //return 0 (not compressed)
    return 0;
}

/**
 * @brief Reads a line from the input until it detects a \\n or \\r
 * 
 * @param text variable that will contain the string
 * @return char* 
 */
char *readLine(char *text){
    char readout;
    //size starts at 1 because of the \0
    int textSize = 1;
    text = NULL;

    do{
        readout = getchar();
        text = (char *)realloc(text, textSize*sizeof(char));
        text[textSize-1] = readout;
        textSize++;
    }while(readout != '\n' && readout != '\r');

    if(readout == '\r')
        readout = getchar();

    //[textSize-2] is used because textSize is incremented in the previous while
    text[textSize-2] = '\0';

    return text;
}

/**
 * @brief prints the amount of coeficients that are less than or equal to 0
 * 
 * @param coef complex array
 * @param length array length
 */
void printNegativeComplex(double complex *coef, int length){
    int counter = 0;
    for(int i = 0; i < length; i++){
        //checking if the real and the imaginary part of this number are <= 0
        if(creal(coef[i]) <= 0 && cimag(coef[i]) <= 0)
            counter++;
    }

    printf("%d\n", counter);
}

/**
 * @brief initializes a array of indexes
 * 
 * @param length array length
 * @return int* index array
 */
int *initializeIndexes(int length){
    int *indexes = (int *)malloc(length * sizeof(int));
    for(int i = 0; i < length; i++){
        indexes[i] = i;
    }
    return indexes;
}

/**
 * @brief calculates the magnitude of a complex number
 * 
 * @param number complex number
 * @return double magnitude
 */
double magnitude(double complex number){
    return sqrt(pow(creal(number), 2) + pow(cimag(number), 2));
}

/**
 * @brief performs a Insertion Sort in a coeficient_t struct
 * 
 * @param coef coeficient_t struct
 * @param size array size
 */
void insertionSort(coeficients_t *coef, int size){
    for(int i = 1; i < size; i++){
        //this sort is based on the magnitude of the complex number
        float key = magnitude(coef->data[coef->indexes[i]]);
        int indexKey = coef->indexes[i];
        int j = i-1;
        while(j >= 0 && magnitude(coef->data[coef->indexes[j]]) < key){
            coef->indexes[j+1] = coef->indexes[j];
            j--;
        }
        //this maintains the order of the data array, only altering the index array order
        coef->indexes[j+1] = indexKey;
    }
}

