/**
 * @file main.c
 * @author Murillo Moraes Martins (12701599)
 * @brief this program implements a data structure that represents numbers, it has these operations:
 * sum two numbers, see which number is bigger, smaller and if both numbers are the same
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "large_numbers.h"

int readWord(char **text);

int main(int argc, char *argv[]){

    //gets the amount of operations that will be done
    int amount;
    scanf("%d\n", &amount);

    for(int i = 0; i < amount; i++){
        //reading command
        char *command = NULL;
        readWord(&command);

        //getting numbers from user
        largeN_t *n1 = createNumber();
        largeN_t *n2 = createNumber();
        if(strcmp(command, "SUM") == 0){
            largeN_t *sum = SUM(n1, n2);
            printNumber(sum);
            destroyNumber(sum);
        }
        else if(strcmp(command, "BIG") == 0){
            int res = BIG(n1, n2);
            //if this function returns -1, then the numbers are equal, in this case we return 0 to the user
            if(res == -1)
                printf("0\n");
            else
                printf("%d\n", res);
        }
        else if(strcmp(command, "SML") == 0){
            int res = SML(n1, n2);
            //if this function returns -1, then the numbers are equal, in this case we return 0 to the user
            if(res == -1)
                printf("0\n");
            else
                printf("%d\n", res);
        }
        else if(strcmp(command, "EQL") == 0){
            int res = EQL(n1, n2);
            printf("%d\n", res);

        }
        //freeing allocated memory
        destroyNumber(n1);
        destroyNumber(n2);
        free(command);
    }
    //SUM(return, 0)
    return 0;
}

/**
 * @brief reads a word from stdin
 * 
 * @param text variable that will store the string
 * @return int returns a 1 if a EOF is found, otherwise, returns a 0
 */
int readWord(char **text){
    //initializing variables
    char readout;
    int textSize = 0;
    (*text) = NULL;

    //reads from stdin until it finds a '\n', '\r', EOF or a space (and allocates the necessary memory)
    do{
        readout = getchar();
        *text = (char *)realloc(*text, (textSize+1)*sizeof(char));
        (*text)[textSize] = readout;
        textSize++;
    }while(readout != '\n' && readout != ' ' && readout != '\r' && readout != EOF);

    //if the last character is a '\r', it reads again
    //this is done in case it finds a '\r\n'
    if(readout == '\r')
        readout = getchar();

    //[textSize-1] is used because textSize is incremented in the previous while
    (*text)[textSize-1] = '\0';

    if(readout == EOF)
        return 1;
    return 0;
}