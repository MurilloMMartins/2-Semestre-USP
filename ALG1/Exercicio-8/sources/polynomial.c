#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "polynomial.h"

typedef struct term{
    int value;
}term_t;

struct polynomial{
    list_t *termList;
    int size;
};

/**
 * @brief function that frees a term
 * 
 * @param t term structure
 */
void free_function(term_t *t){
    free(t);
}

/**
 * @brief function that prints a term from a list
 * 
 * @param t term structure
 * @param state state of said term in a list
 */
void print_function(term_t *t, int state){
    switch(state){
        case -2:
            printf("(%d)", t->value);
            break;
        case -1:
            printf("(%d,", t->value);
            break;
        case 0:
            printf("%d,", t->value);
            break;
        case 1:
            printf("%d)", t->value);
            break;
    }
}

/**
 * @brief create a polynomial structure
 * 
 * @return poly_t* polynomial struct
 */
poly_t *create_polynomial(){
    poly_t *p = (poly_t *)malloc(sizeof(poly_t));
    p->termList = create_list(free_function, print_function);

    //this is necessary because in this case polynomials are formated in this form:
    //(0,1,4,2,3)
    char format = getchar();
    int readout;
    do{
        //reading polynomial value
        scanf("%d", &readout);
        //allocating and initializing variables
        term_t *t = (term_t *)malloc(sizeof(term_t));
        t->value = readout;

        insert_in_list(p->termList, t);
        format = getchar();
    }while(format != ')');

    //accounting for a \r
    format = getchar();
    if(format == '\r')
        format = getchar();

    p->size = list_size(p->termList);

    return p;
}

/**
 * @brief adds two polynomials
 * 
 * @param p1 polynomial struct
 * @param p2 polynomial struct
 * @return poly_t* polynomial struct containing a sum of both polynomials
 */
poly_t *polynomial_sum(poly_t *p1, poly_t *p2){
    //creating a new polynomial struct
    poly_t *sum = (poly_t *)malloc(sizeof(poly_t));
    sum->termList = create_list(free_function, print_function);
    
    //checking which polynomial is bigger
    if(p1->size > p2->size){
        sum->size = p1->size;
        //adding both polynomials
        for(int i = 0; i < p2->size; i++){
            term_t *t1 = remove_from_list(p1->termList);
            term_t *t2 = remove_from_list(p2->termList);

            term_t *tSum = (term_t *)malloc(sizeof(term_t));
            tSum->value = t1->value + t2->value;
            insert_in_list(sum->termList, tSum);

            free(t1);
            free(t2);
        }
        //adding remaining values
        for(int i = 0; i < (p1->size - p2->size); i++){
            insert_in_list(sum->termList, remove_from_list(p1->termList));
        }
    }
    else{
        sum->size = p2->size;
        //adding both polynomials
        for(int i = 0; i < p1->size; i++){
            term_t *t1 = remove_from_list(p1->termList);
            term_t *t2 = remove_from_list(p2->termList);

            term_t *tSum = (term_t *)malloc(sizeof(term_t));
            tSum->value = t1->value + t2->value;
            insert_in_list(sum->termList, tSum);

            free(t1);
            free(t2);
        }
        //adding remaining values
        for(int i = 0; i < (p2->size - p1->size); i++){
            insert_in_list(sum->termList, remove_from_list(p2->termList));
        }
    }

    return sum;
}

/**
 * @brief prints a polynomial
 * 
 * @param p polynomial struct
 */
void print_polynomial(poly_t *p){
    print_list(p->termList);
}

/**
 * @brief frees all memory allocated for a polynomial struct
 * 
 * @param p polynomial struct
 */
void destroy_polynomial(poly_t *p){
    destroy_list(p->termList);
    free(p);
}