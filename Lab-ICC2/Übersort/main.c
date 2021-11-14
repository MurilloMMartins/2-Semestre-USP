/**
 * @file main.c
 * @author Murillo Moraes Martins (12701599)
 * @brief this program implements a quicksort using certain adjustments, in this case it either
 * selects a random pivot or the median for the first, middle and last elements from each partition.
 * Beyond that it also partitions the array into 3 parts(one smaller than, equal and greater than the 
 * pivot), lastly it uses Insetion Sort to sort all partitions that have a size smaller or equal than 10.
 * @version 0.1
 * @date 2021-11-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct partition{
    int start;
    int end;
}part_t;

void UberSort(int *v, int start, int end, int (*pivotFunc) ());
part_t partition(int *v, int start, int end);
void InsertionSort(int *vector, int start, int end);
void swap(int *a, int *b);
int RandomPivot(int *v, int start, int end);
int MedianPivot(int *v, int start, int end);
void printArray(int *v, int size);
int *createArray(int size);

int main(int argc, char *argv[]){
    srand(42);

    //getting input from user
    int size;
    char method;
    scanf("%d\n", &size);
    scanf("%c\n", &method);
    int *v = createArray(size);

    //choosing which pivot method will be used in quicksort
    switch (method){
        case '1':
            UberSort(v, 0, size-1, MedianPivot);
            break;

        case '2':
            UberSort(v, 0, size-1, RandomPivot);
            break;
    }

    printArray(v, size);
    free(v);

    //0 nruter
    return 0;
}

/**
 * @brief sorts a array similarly to QuickSort's way of sorting
 * 
 * @param v array
 * @param start starting index of the array
 * @param end final index in the array
 * @param pivotFunc function to choose the pivot
 */
void UberSort(int *v, int start, int end, int (*pivotFunc) ()){
    //if a array has a size that is <= 10, sort using insertion sort
    if((end+1) - start <= 10){
        InsertionSort(v, start, end);
        return;
    }

    //choosing pivot and swapping it with the last element
    int p = pivotFunc(v, start, end);
    swap(&v[p], &v[end]);

    //partitioning pivot into three parts
    part_t part = partition(v, start, end);

    //recursive step
    UberSort(v, start, part.start, pivotFunc);
    UberSort(v, part.end, end, pivotFunc);
}

/**
 * @brief partitions a array around a pivot, this creates 3 partitions, one smaller than the pivot,
 * other equal to the pivot and other greater than the pivot. Returns a partition struct that determines
 * where the partitions are divided
 * 
 * @param v array
 * @param start start of the array
 * @param end end of the arrat
 * @return part_t parition created
 */
part_t partition(int *v, int start, int end){
    //initializing variables
    int i = start;
    int m = start;
    int j = end-1;

    part_t part;
    int p = end;

    //running across the array
    while (m <= j){
        //swapping if needed
        if(v[m] < v[p]){
            swap(&v[m], &v[i]);
            i++;
            m++;
        }
        else if(v[m] == v[p]){
            m++;
        }
        else if(v[m] > v[p]){
            swap(&v[m], &v[j]);
            j--;
        }
    }

    //changing pivot into its right position
    swap(&v[m], &v[p]);

    part.start = i - 1;
    part.end = m + 1;

    return part;
}

/**
 * @brief sorts a array
 * 
 * @param vector array
 * @param start start of the array
 * @param end end of the array
 */
void InsertionSort(int *vector, int start, int end){
    for(int i = start + 1; i < end+1; i++){
        int key = vector[i];
        int j = i-1;
        while(j >= start && vector[j] > key){
            vector[j+1] = vector[j];
            j--;
        }
        vector[j+1] = key;
    }
}

/**
 * @brief swaps two integers
 * 
 * @param a 
 * @param b 
 */
void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * @brief generates a random value of pivot given the size of a array
 * 
 * @param v array
 * @param start start of the array
 * @param end end of the array
 * @return int pivot index
 */
int RandomPivot(int *v, int start, int end){
    return start + (rand() % (end - start + 1));
}

/**
 * @brief returns the index of the median between
 * 
 * @param v array
 * @param start start of the array
 * @param end end of the array
 * @return int pivot index
 */
int MedianPivot(int *v, int start, int end){
    //calculating the middle
    int middle = (end + start + 1)/2;
    
    //returning median
    if((v[start] <= v[middle] && v[start] >= v[end]) || (v[start] <= v[end] && v[start] >= v[middle]))
        return start;
    if((v[middle] <= v[start] && v[middle] >= v[end]) || (v[middle] <= v[end] && v[middle] >= v[start]))
        return middle;
    if((v[end] <= v[start] && v[end] >= v[middle]) || (v[end] <= v[middle] && v[end] >= v[start]))
        return end;

    //this should never happen
    return -1;
}

/**
 * @brief prints a array
 * 
 * @param v array
 * @param size size of the array
 */
void printArray(int *v, int size){
    for(int i = 0; i < size; i++)
        printf("%d\n", v[i]);
}

/**
 * @brief creates a array and returns it
 * 
 * @param size size of the array
 * @return int* array
 */
int *createArray(int size){
    int *v = (int *)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++){
        scanf("%d\n", &v[i]);
    }

    return v;
}