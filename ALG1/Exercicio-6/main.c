/*
 * Subject: Algorithms and Data Structures 1 
 *
 * Title: Rotating list
 * 
 * Functionality: This program is designed to show how you can rotate the elements in a linked list.
 * 
 * Name: Murillo Moraes Martins
 * 
 * USP number: 12701599
 *
 * Date of the last modification: 30/09/2021
*/

#include <stdio.h>
#include "list.h"

int main(int argc, char *argv[]){
    //amount of tests that will be done
    int testAmount;
    scanf(" %d", &testAmount);

    for(int i = 0; i < testAmount; i++){
        int listSize, rotations;
        scanf(" %d %d", &listSize, &rotations);

        //creating and filling the list
        list_t *list = create();
        for(int j = 0; j < listSize; j++){
            int data;
            scanf(" %d", &data);
            insert(list, data);
        }

        //rotating the elements the amount of times the user wants
        for(int j = 0; j < rotations; j++){
            rotate(list);
        }

        printList(list);
        //deallocating memory for the next test
        destroy(list);
    }

    //let's gooo, return 0 baby!!
    return 0;
}