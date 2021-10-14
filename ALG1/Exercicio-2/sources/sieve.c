#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0

/**
 * @brief function based on the sieve of eratosthenes, it recieves two arrays, one composed of 
 * ordered numbers(0 to MAX_SIZE) and the other composed only of TRUE values (or 1). This function then
 * discovers the prime numbers between 0 and MAX_SIZE and sets to FALSE the values which are not prime
 * 
 * @param numbers array composed of the numbers between 0 and MAX_SIZE
 * @param isItPrime array composed of only TRUE values, it needs to have the same size as the previous array
 */
void SieveOfEratosthenes(int *numbers, int *isItPrime, int MAX_SIZE){
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
void findPrimes(queue_t *primeQueue, int *numbers, int *isItPrime, int index, int MAX_SIZE){
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