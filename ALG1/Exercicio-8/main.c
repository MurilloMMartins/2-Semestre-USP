/**
 * @file main.c
 * @author Murillo Moraes Martins (NºUSP 12701599)
 * @brief This program has the functionality of adding multiple polynomials, according to user input
 * @version 0.1
 * @date 2021-11-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

int main(int argc, char *argv[]){
    int testCases;
    scanf("%d\n", &testCases);

    for(int i = 0; i < testCases; i++){
        int polynomAmount;
        scanf("%d\n", &polynomAmount);
        poly_t *total;
        
        //checking if we will add polynoms or just print one polynom
        if(polynomAmount == 1){
            total = create_polynomial();
        }
        else{
            for(int j = 1; j < polynomAmount; j++){
                if(j == 1){
                    //this only happens for the first two polynoms to be added
                    poly_t *p1 = create_polynomial();
                    poly_t *p2 = create_polynomial();
                    total = polynomial_sum(p1, p2);
                    destroy_polynomial(p1);
                    destroy_polynomial(p2);
                }
                else{
                    //here we need a auxiliar struct to be able to sum more polynoms
                    poly_t *p = create_polynomial();
                    poly_t *aux = polynomial_sum(total, p);
                    destroy_polynomial(p);
                    destroy_polynomial(total);
                    total = aux;
                }
            }
        }
        print_polynomial(total);
        destroy_polynomial(total);
    }
    //return^0
    return 0;
}