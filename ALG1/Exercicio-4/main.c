/*
 * Subject: Algorithms and Data Structures 1 
 *
 * Title: Priority Queue
 * 
 * Functionality: This program creates hospital queue. Naturally this queue has a priority between
 * the patients in the queue, this order being based on whether or not this person is old (age >= 60)
 * and if this person has any aggravating health condition. So basically this program builds this queue
 * and orders everyone based on their priority in the queue. So when adding new people, you can guarantee
 * they will "go out of the queue" in the priority's order.
 * 
 * Name: Murillo Moraes Martins
 * 
 * USP number: 12701599
 *
 * Date of the last modification: 20/09/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int readWord(char **text);
int decidePriority(int age, int hasIllness);
int findNextQueue(int index, queue_t *priority[index]);

int main(){
    //creating the priority queue
    queue_t *priority[4];
    for(int i = 0; i < 4; i++){
        priority[i] = create();
    }

    //getting the amount of actions the user will want
    int actions;
    scanf("%d", &actions);

    for(int i = 0; i < actions; i++){
        char *action;
        //getting rid of any remaining \r or \n
        scanf("%*[\r\n]s");
        readWord(&action);

        //selecting whether a element will be added or removed from the queue
        if(strcmp(action, "ENTRA") == 0){
            //initializing variables with the data of a person
            char *name;
            int age, hasIllness;
            readWord(&name);
            scanf(" %d %d", &age, &hasIllness);

            //control to determine whether or not the queue is full
            int control = 1;
            //deciding which queue a person will be a part of and enqueuing said person
            control = enqueue(priority[decidePriority(age, hasIllness)], name, age, hasIllness);
            free(name);

            if(control == 0)
                printf("FILA CHEIA\n");
        }
        else if(strcmp(action, "SAI") == 0){
            //creating the variables that will recieve the data of a person
            char *name = NULL;
            int age, hasIllness;

            //finding which queue needs to be emptied
            int index = findNextQueue(0, priority);
            
            if(index == -1){
                printf("FILA VAZIA\n");
            }
            else{
                //dequeuing and printing the data from a person
                dequeue(priority[index], &name, &age, &hasIllness);
                printf("%s %d %d\n", name, age, hasIllness);
                free(name);
            }
        }

        free(action);
    }

    //deallocating memory
    for(int i = 0; i < 4; i++){
        destroy(priority[i]);
    }

    //and finally, return 0, thank you for coming to my TED Talk
    return 0;
}

/**
 * @brief reads a word from stdin
 * 
 * @param text variable that will store the string
 * @return int returns a 1 if a \n is found, otherwise, returns a 0
 */
int readWord(char **text){
    //initializing variables
    char readout;
    int textSize = 0;
    (*text) = NULL;

    //reads from stdin until it finds a '\n', '\r' or a space (and allocates the necessary memory)
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

    if(readout == '\n')
        return 1;
    return 0;
}

/**
 * @brief decides which queue a person will enter, being 0 the highest one and 3 the lowest
 * 
 * @param age value containing a person's age
 * @param hasIllness 0 if a person has a illness, 1 otherwise
 * @return int the index of the queue the person will be joining
 */
int decidePriority(int age, int hasIllness){
    if(age >= 60 && hasIllness == 1) return 0;
    if(age < 60 && hasIllness == 1) return 1;
    if(age >= 60 && hasIllness == 0) return 2;
    if(age < 60 && hasIllness == 0) return 3;

    return -1;
}

/**
 * @brief recursive function that returns the index of a non-empty queue based on the priority of them
 * 
 * @param index initial searching index
 * @param priority array of the queue struct
 * @return int the index of that queue or -1 if all queues are empty
 */
int findNextQueue(int index, queue_t *priority[4]){
    //base case
    if(index == 4)
        return -1;
    
    if(isEmpty(priority[index]) == 1)
        return findNextQueue(index + 1, priority); //recursive step
    else
        return index;                              //base case
}