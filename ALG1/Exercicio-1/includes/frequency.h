#ifndef FREQUENCY_H
#define FREQUENCY_H

typedef struct counter{
    char **words;
    int *amounts;
    int size;
}counter_t;

int isUniqueWord(counter_t *counter, char *word);
void initializeStruct(counter_t *counter);
void addUniqueWord(counter_t *counter, char *word);
void destroyStruct(counter_t *counter);
void sortNumbers(int *indexesArray, int *amountsArray, int size);
void sortWords(counter_t *counter, int *amountsArray);
int isWordBiggerThan(char *word1, char *word2);

#endif