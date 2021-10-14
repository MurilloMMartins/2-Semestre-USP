/*
 * Subject: Algorithms and Data Structures 1 
 *
 * Title: Balanced Sequence
 * 
 * Functionality: This program returns whether a sequence is balanced. A balanced sequence is a sequence
 * is defined as a string that has all delimitators (brackets, parenthesis, braces and quotes) "closed".
 * 
 * Name: Murillo Moraes Martins
 * 
 * USP number: 12701599
 *
 * Date of the last modification: 29/09/2021
*/

#include <stdio.h>
#include "stack.h"

int main(int argc, char *argv[]){
    int input;
    do{
        input = getchar();

        //initializing the stack struct
        stack_t *sequence;
        sequence = create();

        //variable that will hold popped values
        char elem;
        //control value
        int control;
        //if a string is "balanced"
        int isBalanced = 1;
        //counts quotations
        int quotationCounter = 0;
        while(input != '\n' && input != EOF){
            //this if sequence checks whether we will pop or push to the stack
            if(input == ']'){
                control = pop(sequence, &elem);
                if(control == -1 || elem != '['){
                    isBalanced = 0;
                }
            }
            else if(input == ')'){
                control = pop(sequence, &elem);
                if(control == -1 || elem != '('){
                    isBalanced = 0;
                }
            }
            else if(input == '}'){
                control = pop(sequence, &elem);
                if(control == -1 || elem != '{'){
                    isBalanced = 0;
                }
            }
            else if(input == '"'){  //for some reason vscode just doesn't work properly after this line(but the program does)
                quotationCounter++;
            }
            else{
                //pushes any remaining characters (except spaces)
                if(input != ' ')
                    push(sequence, input);
            }

            input = getchar();
            if(input == '\r')
                //checks if we've found a \r (and consumes a \n if we do)
                input = getchar();
        }

        //if we have a odd number of quotations, our string isn't balanced
        if(quotationCounter % 2 != 0){
            isBalanced = 0;
        }

        if(isBalanced == 1){
            printf("BALANCEADO");
        }
        else{
            printf("NÃO BALANCEADO");
        }

        //deletes the sequence
        delete(sequence);

        //prints \n if we haven't reached the end of the file yet
        if(input != EOF){
            printf("\n");
        }
    }while(input != EOF);
    
    //no functions for you, only a return 0
    return 0;
}