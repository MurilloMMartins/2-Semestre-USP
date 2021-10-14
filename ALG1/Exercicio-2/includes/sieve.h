#ifndef SIEVE_H
#define SIEVE_H

void SieveOfEratosthenes(int *numbers, int *isItPrime, int MAX_SIZE);
void findPrimes(queue_t *primeQueue, int *numbers, int *isItPrime, int index, int MAX_SIZE);
void printPrimes(queue_t *primeQueue);

#endif