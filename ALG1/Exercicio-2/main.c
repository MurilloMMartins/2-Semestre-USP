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
#include "sieve.h"

//defining the max size of the sieve
#define MAX_SIZE 10000
#define TRUE 1
#define FALSE 0

int main(){
    //arrays that will hold information about the prime numbers
    int numbers[MAX_SIZE];
    int isItPrime[MAX_SIZE];

    //initializing arrays
    for(int i = 0; i < MAX_SIZE; i++){
        numbers[i] = i;
        isItPrime[i] = TRUE;
    }

    SieveOfEratosthenes(numbers, isItPrime, MAX_SIZE);
    
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
        findPrimes(primesQueue, numbers, isItPrime, primeIndex, MAX_SIZE);
    }

    printPrimes(primesQueue);
    destroy(primesQueue);

    return 0;
}