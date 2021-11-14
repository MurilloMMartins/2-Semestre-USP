#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "large_numbers.h"

typedef struct node node_t;
struct node{
    node_t *next, *prev;
    int value;
};

struct largeNumber{
    node_t *head, *tail;
    int sign;
    int size;
};

/**
 * @brief inserts a integer in a list
 * 
 * @param l list struct
 * @param data integer to be inserted
 */
void insert_in_list(largeN_t *l, int data){
    node_t *n = (node_t *)malloc(sizeof(node_t));
    n->value = data;
    n->next = NULL;
    n->prev = NULL;

    if(l->head == NULL){
        //inserting the first item in the list
        l->head = n;
        l->tail = n;
    }
    else{
        //inserting other itens in the list
        l->tail->next = n;
        n->prev = l->tail;
        l->tail = n;
    }
    l->size++;
}

/**
 * @brief creates a large number struct
 * 
 * @return largeN_t* large number struct
 */
largeN_t *createNumber(){
    //initializing struct
    largeN_t *n = (largeN_t *)malloc(sizeof(largeN_t));
    n->head = NULL;
    n->tail = NULL;
    n->size = 0;

    //checking if we have a positive number or a negative number
    char data = getchar();
    if(data == '-')
        n->sign = -1;
    else{
        ungetc(data, stdin);
        n->sign = 1;
    }

    //excluding an 0s before the first significant digit
    data = getchar();
    int zeros = data - '0';
    while(zeros == 0){
        data = getchar();
        zeros = data - '0';
    }
    ungetc(data, stdin);

    //getting all the remaining numbers from the user
    do{
        data = getchar();
        if(data != '\n' && data != ' ' && data != '\r'){
            int value = data - '0';
            insert_in_list(n, value);
        }

        if(data == '\r')
            data = getchar();

    }while(data != '\n' && data != ' ');

    return n;
}

/**
 * @brief sums two numbers
 * 
 * @param n1 first number
 * @param n2 second number
 * @return largeN_t* sum of both numbers
 */
largeN_t *SUM(largeN_t *n1, largeN_t *n2){
    //initializing number struct
    largeN_t *sum = (largeN_t *)malloc(sizeof(largeN_t));
    sum->head = NULL;
    sum->tail = NULL;
    sum->size = 0;

    //initializing usefull variables
    node_t *aux1 = n1->head;
    node_t *aux2 = n2->head;
    int size1 = n1->size;
    int size2 = n2->size;

    //if one number is bigger than the other, we copy the elements that can't be summed from the biggest number
    if(size1 > size2){
        while(size1 > size2){
            insert_in_list(sum, aux1->value);
            aux1 = aux1->next;
            size1--;
        }
        //assigning the sign of the biggest number to our sum
        sum->sign = n1->sign;
    }
    else{
        while(size2 > size1){
            insert_in_list(sum, aux2->value);
            aux2 = aux2->next;
            size2--;
        }
        //assigning the sign of the biggest number to our sum
        sum->sign = n2->sign;
    }

    //summing two numbers
    while(aux1 != NULL && aux2 != NULL){
        int total = aux1->value + aux2->value;

        //if the sum if bigger than 10 we add 1 to the previous element or add a new starting 
        //element with value 1 to the start
        if(total >= 10){
            total -= 10;
            node_t *auxSum = sum->tail;
            //going back in the list and adding 1 to elements
            while(auxSum != NULL){
                auxSum->value++;
                if(auxSum->value >= 10){
                    auxSum->value -= 10;
                    auxSum = auxSum->prev;
                }
                else{
                    break;
                }
            }
            
            //this only happens if we reach the start of the list
            //in this case we add 1 as the fist element
            //for example: 9 + 9 = 18 (here 1 is added to the start)
            if(auxSum == NULL){
                node_t *n = (node_t *)malloc(sizeof(node_t));
                n->value = 1;
                n->next = NULL;
                n->prev = NULL;
                if(sum->head == NULL){
                    //if we have no elements in this list
                    sum->head = n;
                    sum->tail = n;
                }
                else{
                    //if we alread have elements
                    sum->head->prev = n;
                    n->next = sum->head;
                    sum->head = n;
                }
            }
        }

        //inserting in list and progressing through the sum
        insert_in_list(sum, total);
        aux1 = aux1->next;
        aux2 = aux2->next;
    }

    return sum;

}

/**
 * @brief returns if n1 is bigger than n2, if they are the same it returns -1
 * 
 * @param n1 first number
 * @param n2 second number
 * @return int returns 1 if first is bigger, 0 if second is bigger, -1 if they are the same
 */
int BIG(largeN_t *n1, largeN_t *n2){
    //checking if the signs are different(meaning one is negative and one is positive)
    if(n1->sign > n2->sign) return 1;
    if(n1->sign < n2->sign) return 0;

    //if both are positive we return one thing
    //if they are both negative we return the oposite(because 1 < 2 and -1 > -2)
    if(n1->sign == 1 && n2->sign == 1){
        //checking if one number is bigger than the other
        if(n1->size > n2->size) return 1;
        if(n1->size < n2->size) return 0;

        node_t *aux1 = n1->head;
        node_t *aux2 = n2->head;
        //comparing all elements until we find one that is bigger(if we don't find it, than the are equal)
        while(aux1 != NULL && aux2 != NULL){
            if(aux1->value > aux2->value) return 1;
            if(aux1->value < aux2->value) return 0;
            aux1 = aux1->next;
            aux2 = aux2->next;
        }
    }
    else if(n1->sign == -1 && n2->sign == -1){
        //same as above, but return the oposite
        if(n1->size > n2->size) return 0;
        if(n1->size < n2->size) return 1;

        node_t *aux1 = n1->head;
        node_t *aux2 = n2->head;
        while(aux1 != NULL && aux2 != NULL){
            if(aux1->value > aux2->value) return 0;
            if(aux1->value < aux2->value) return 1;
            aux1 = aux1->next;
            aux2 = aux2->next;
        }
    }

    return -1;
}

/**
 * @brief returns if n1 is smaller than n2, if they are the same it returns -1
 * 
 * @param n1 first number
 * @param n2 second number
 * @return int returns 1 if first is smaller, 0 if second is smaller, -1 if they are the same
 */
int SML(largeN_t *n1, largeN_t *n2){
    //using the BIG function because they are the same but inverted;
    int res = BIG(n1, n2);

    if(res == -1) return -1;
    return !res;
}

/**
 * @brief returns if n1 is equal to n2
 * 
 * @param n1 first number
 * @param n2 second number
 * @return int returns 1 if the are the same, 0 otherwise
 */
int EQL(largeN_t *n1, largeN_t *n2){
    if(BIG(n1, n2) == -1) return 1;
    return 0;
}

/**
 * @brief prints a number struct
 * 
 * @param n large number struct
 */
void printNumber(largeN_t *n){
    //printing the sign if necessary
    if(n->sign == -1)
        printf("-");

    //progressing through the struct and printing values
    node_t *aux = n->head;
    while(aux != NULL){
        printf("%d", aux->value);
        aux = aux->next;
    }
    printf("\n");
}

/**
 * @brief deallocates memory allocated in a number struct
 * 
 * @param n large number struct
 */
void destroyNumber(largeN_t *n){
    node_t *aux = n->head;
    while(aux != NULL){
        n->head = aux->next;
        free(aux);
        //progressing through list
        aux = n->head;
    }
    free(n);
}