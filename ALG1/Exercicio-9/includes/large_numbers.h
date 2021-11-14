#ifndef LARGE_NUMBERS_H
#define LARGE_NUMBERS_H

typedef struct largeNumber largeN_t;

largeN_t *createNumber();
largeN_t *SUM(largeN_t *n1, largeN_t *n2);
int BIG(largeN_t *n1, largeN_t *n2);
int SML(largeN_t *n1, largeN_t *n2);
int EQL(largeN_t *n1, largeN_t *n2);
void printNumber(largeN_t *n);
void destroyNumber(largeN_t *n);

#endif