/*
 * Subject: Algorithms and Data Structures 1 
 *
 * Title: Sorted List
 * 
 * Functionality: This program implements a generic sorted list. This list is used as a data bank.
 * This data bank stores people (name and ID).
 * 
 * Name: Murillo Moraes Martins
 * 
 * USP number: 12701599
 *
 * Date of the last modification: 30/09/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted_list.h"

typedef struct person{
    int ID;
    char *name;
}person_t;

int readLine(char **text);
int readWord(char **text);
void freePerson(person_t *p);
int compareID(person_t *firstP, person_t *secondP);
void printPerson(person_t *p);


int main(int argc, char *argv[]){

    list_t *list = create_list(freePerson, compareID, printPerson);
    int foundEOF;
    do{
        //reading commands
        char *command;
        foundEOF = readWord(&command);

        //executing commands
        if(strcmp(command, "INSERE") == 0){
            //creating person struct
            person_t *p = (person_t *)malloc(sizeof(person_t));
            scanf(" %d ", &p->ID);
            readLine(&p->name);

            insert_in_list(list, p);
        }
        else if(strcmp(command, "REMOVE") == 0){
            //create a person struct will a NULL name
            //this is done because we will only compare if a ID exists and remove if it does
            person_t *p = (person_t *)malloc(sizeof(person_t));
            scanf(" %d\n", &p->ID);
            p->name = NULL;

            remove_from_list(list, p);
        }
        else if(strcmp(command, "IMPRIMIR") == 0){
            print_list(list);
        }
        free(command);

    }while(foundEOF != 1);
    
    destroy_list(list);

    //(*return) (0)
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

/**
 * @brief reads a word from stdin
 * 
 * @param text variable that will store the string
 * @return int returns a 1 if a EOF is found, otherwise, returns a 0
 */
int readLine(char **text){
    //initializing variables
    char readout;
    int textSize = 0;
    (*text) = NULL;

    //reads from stdin until it finds a '\n', '\r' or a EOF (and allocates the necessary memory)
    do{
        readout = getchar();
        *text = (char *)realloc(*text, (textSize+1)*sizeof(char));
        (*text)[textSize] = readout;
        textSize++;
    }while(readout != '\n' && readout != '\r' && readout != EOF);

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

/**
 * @brief frees a person struct
 * 
 * @param p person struct
 */
void freePerson(person_t *p){
    //its important to check if the name is NULL because there will be situations where the name will be NULL
    if(p->name != NULL)
        free(p->name);
    free(p);
}

/**
 * @brief compares two IDs from a person struct and returns whether the first ID is bigger(1), 
 * smaller(-1) or equal(0) to the second
 * 
 * @param firstP first person struct
 * @param secondP second person struct
 * @return int returns the relation between both IDs
 */
int compareID(person_t *firstP, person_t *secondP){
    if(firstP->ID > secondP->ID)
        return 1;
    else if(firstP->ID < secondP->ID)
        return -1;
    else
        return 0;
}

/**
 * @brief prints a person struct
 * 
 * @param p person struct
 */
void printPerson(person_t *p){
    printf("%d, %s; ", p->ID, p->name);
}
