/*
 * Subject: Algorithms and Data Structures 1 
 *
 * Title: Sieve of Erastosthenes
 * 
 * Functionality: This program finds all primes between 0 and MAX_SIZE using the Sieve of Eratosthenes
 * algorithm, after that it prints N amount of primes with M indexes, N and M being integers that will
 * be inputed by the user.
 * 
 * Name: Murillo Moraes Martins
 * 
 * USP number: 12701599
 *
 * Date of the last modification: 19/09/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//defining the max size of the sieve
#define MAX_SIZE 10000
#define TRUE 1
#define FALSE 0

void SieveOfEratosthenes(int *numbers, int *isItPrime);
void findPrimes(queue_t *primeQueue, int *numbers, int *isItPrime, int index);
void printPrimes(queue_t *primeQueue);

int main(){
    //arrays that will hold information about the prime numbers
    int numbers[MAX_SIZE];
    int isItPrime[MAX_SIZE];

    //initializing arrays
    for(int i = 0; i < MAX_SIZE; i++){
        numbers[i] = i;
        isItPrime[i] = TRUE;
    }

    SieveOfEratosthenes(numbers, isItPrime);
    
    //getting amount of numbers that will be printed in the screen
    int primesToBePrinted;
    scanf(" %d", &primesToBePrinted);

    //creating queue
    queue_t *primesQueue;
    primesQueue = create(primesToBePrinted);

    //finding all the primes that the user wants to be displayed on the screen
    for(int i = 0; i < primesToBePrinted; i++){
        int primeIndex;
        scanf(" %d", &primeIndex);
        findPrimes(primesQueue, numbers, isItPrime, primeIndex);
    }

    printPrimes(primesQueue);
    destroy(primesQueue);

    return 0;
}

/**
 * @brief function based on the sieve of eratosthenes, it recieves two arrays, one composed of 
 * ordered numbers(0 to MAX_SIZE) and the other composed only of TRUE values (or 1). This function then
 * discovers the prime numbers between 0 and MAX_SIZE and sets to FALSE the values which are not prime
 * 
 * @param numbers array composed of the numbers between 0 and MAX_SIZE
 * @param isItPrime array composed of only TRUE values, it needs to have the same size as the previous array
 */
void SieveOfEratosthenes(int *numbers, int *isItPrime){
    for(int i = 2; i < MAX_SIZE; i++){
        if(isItPrime[i] == TRUE){
            for(int j = i + 1; j < MAX_SIZE; j++){
                if(numbers[j] % numbers[i] == 0)
                    isItPrime[j] = FALSE;
            }
        }
    }
}

/**
 * @brief function that enqueues the prime values that the user wants(in this case if you input 1, 
 * it finds the first prime, if ou input 10, it finds the tenth prime and so on)
 * 
 * @param primeQueue queue struct
 * @param numbers array composed of the numbers between 0 and MAX_SIZE
 * @param isItPrime array composed of only TRUE values, it needs to have the same size as the previous array
 * @param index the value that will be enqueued
 */
void findPrimes(queue_t *primeQueue, int *numbers, int *isItPrime, int index){
    int primesFound = 0;
    for(int i = 2; i < MAX_SIZE; i++){
        if(isItPrime[i] == TRUE){
            primesFound++;
            if(primesFound == index){
                enqueue(primeQueue, numbers[i]);
                return;
            }
        }
    }
}

/**
 * @brief dequeues every element from the queue
 * 
 * @param primeQueue queue struct
 */
void printPrimes(queue_t *primeQueue){
    while(isEmpty(primeQueue) != TRUE){
        int prime;
        dequeue(primeQueue, &prime);
        printf("%d ", prime);
    }
}