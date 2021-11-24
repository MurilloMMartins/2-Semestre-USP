/**
 * @file main.c
 * @author Murillo Moraes Martins (NºUSP: 12701599)
 * @brief This program simulates a process scheduler. Processes are defined by a ID, the stating time that
 * it will enter the scheduler, the amount of operations that will be done and a priority. The scheduler
 * then inserts each process in a list in its appopriate time and priority, if it inserts a process
 * with a bigger priority than the current process it goes back to the first element containing the said bigger
 * priority. The program ends when all processes have been finished, printing the time they finished in the screen.
 * @version 0.1
 * @date 2021-11-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct process{
    int id, initial, amount, priority;
}process_t;

typedef struct node node_t;
struct node{
    node_t *next, *prev;
    process_t *process;  
};

typedef struct list{
    node_t *head;
    int size;
} list_t;

process_t *read_process();
void sort_initials(process_t **p, int size);
int compare_process(process_t *p1, process_t *p2);

list_t *create_list();
void insert_process(list_t *l, process_t *p);
void remove_process(list_t *l, process_t *p);
void destroy_list(list_t *l);
node_t *return_to_bigger_priority(list_t *l, node_t *c, int priority);

int main(int argc, char *argv[]){

    //initializing variables
    int processAmount = 0;
    process_t **processArray = NULL;

    //reading processes from the user
    char readout = getchar();
    while(readout != EOF){
        ungetc(readout, stdin);

        processAmount++;
        processArray = (process_t **)realloc(processArray, processAmount * sizeof(process_t *));
        processArray[processAmount-1] = read_process();

        //checking if a id already exists and incrementing if so
        for(int i = 0; i < processAmount-1; i++){
            if(processArray[i]->id == processArray[processAmount-1]->id)
                processArray[processAmount-1]->id++;
        }

        //avoiding \r and \n
        scanf("%*[\r\n]s");
        readout = getchar();
    }

    sort_initials(processArray, processAmount);

    list_t *list = create_list();

    //initializing variables
    node_t *curr = list->head;
    //quantum is used as a measurement of time
    int quantum = 0;
    int included = 0;
    while(included != processAmount || list->size > 0){

        //this happens if we didn't include all our elements from the processesArray inside our list
        if(included < processAmount){
            for(int i = 0; i < processAmount; i++){
                if(quantum == processArray[i]->initial){
                    insert_process(list, processArray[i]);
                    //in case we include a element with a bigger priority than the current one, we go back 
                    //to the first element with said bigger priority
                    if(curr != NULL && processArray[i]->priority > curr->process->priority){
                        curr = return_to_bigger_priority(list, curr, processArray[i]->priority);
                    }
                    included++;
                }
            }
        }

        //this is needed to initialize our curr variable once we add the first element
        if(curr == NULL)
            curr = list->head;

        if(curr != NULL){
            curr->process->amount--;
            curr = curr->next;
            //if a process is over we take it out of our list
            if(curr->prev->process->amount == 0){
                printf("%d %d\n", curr->prev->process->id, quantum);
                remove_process(list, curr->prev->process);
            }
        }
        quantum++;
    }

    //deallocating memory
    destroy_list(list);
    for(int i = 0; i < processAmount; i++){
        free(processArray[i]);
    }
    free(processArray);

    //return -> 0
    return 0;
}

/**
 * @brief reads a process from stdin and returns its struct
 * 
 * @return process_t* process struct containing the process's data
 */
process_t *read_process(){
    process_t *p = (process_t *)malloc(sizeof(process_t));

    int readout;
    scanf(" %d", &readout);
    p->id = readout;
    scanf(" %d", &readout);
    p->initial = readout;
    scanf(" %d", &readout);
    p->amount = readout;
    scanf(" %d", &readout);
    p->priority = readout;

    return p;
}

/**
 * @brief sorts a array containing processes based on their initial time to be inserted
 * 
 * @param p processes array
 * @param size size of the array
 */
void sort_initials(process_t **p, int size){
    //this is a modified insertion sort...
    //don't tell anyone
    for(int i = 1; i < size; i++){
        process_t *key = p[i];
        int j = i-1;
        while(j >= 0 && p[j]->initial > key->initial){
            p[j+1] = p[j];
            j--;
        }
        p[j+1] = key;
    }
}

/**
 * @brief compares two processes and returns which is deserves more priority
 * 
 * @param p1 first process
 * @param p2 second process
 * @return int which has higher priority
 */
int compare_process(process_t *p1, process_t *p2){
    if(p1->priority < p2->priority)
        return 2;
    else if(p1->priority > p2->priority)
        return 1;
    //if they have the same priority we decide using their ID
    else if(p1->priority == p2->priority){
        if(p1->id < p2->id)
            return 1;
        if(p1->id > p2->id)
            return 2;
    }

    //if both the ID and priority are the same they are the same process
    return 0;
}

/**
 * @brief initializes a doubly circular linked list struct
 * 
 * @return list_t* initialized struct
 */
list_t *create_list(){
    list_t *l = (list_t *)malloc(sizeof(list_t));
    l->head = NULL;
    l->size = 0;

    return l;
}

/**
 * @brief inserts a process in a linked list
 * 
 * @param l list structure
 * @param p process to be inserted
 */
void insert_process(list_t *l, process_t *p){
    //allocating new node
    node_t *n = (node_t *)malloc(sizeof(node_t));
    n->process = p;

    //case we want to insert a element in a empty list
    if(l->head == NULL){
        l->head = n;
        l->head->next = n;
        l->head->prev = n;
        l->size++;
        return;
    }

    //case if we want to insert a element in a one element list
    if(l->size == 1){
        l->head->next = n;
        l->head->prev = n;
        n->next = l->head;
        n->prev = l->head;
        
        //this decides whether we want to insert a process before or after the first one
        if(compare_process(l->head->process, n->process) == 2)
            l->head = n;
        
        l->size++;
        return;
    }

    //going through the list until we find the right place to place the new process
    node_t *aux = l->head;
    while(aux->next != l->head && compare_process(aux->process, n->process) == 1)
        aux = aux->next;

    //this is to guarantee we will check all the elements in the list
    if(compare_process(aux->process, n->process) == 1)
        aux = aux->next;

    node_t *prev = aux->prev;
    prev->next = n;
    n->prev = prev;
    aux->prev = n;
    n->next = aux;

    //this changes the new process to the head of the list if it is the new highest one
    if(compare_process(l->head->process, n->process) == 2)
        l->head = n;
    
    l->size++;
}

/**
 * @brief removes a process from the list
 * 
 * @param l list structure
 * @param p process to be removed
 */
void remove_process(list_t *l, process_t *p){

    if(l->head == NULL)
        return;
    
    if(l->size == 1){
        free(l->head);
        l->head = NULL;
        l->size--;
        return;
    }

    //going through the list to find the process we want to remove
    node_t *aux = l->head;
    while(aux->next != l->head && compare_process(aux->process, p) != 0)
        aux = aux->next;

    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;
    
    //if we remove the head of the list we need it to be the next element
    if(compare_process(l->head->process, p) == 0)
        l->head = l->head->next;
    free(aux);
    l->size--;
}

/**
 * @brief destroys a list struct and deallocates memory
 * 
 * @param l list struct
 */
void destroy_list(list_t *l){
    node_t *aux = l->head;
    for(int i = 0; i < l->size; i++){
        l->head = l->head->next;
        free(aux);
        aux = l->head;
    }
    free(l);
}

/**
 * @brief returns the first element in the list that has the priority variable's priority
 * 
 * @param l list struct
 * @param c current node
 * @param priority priority variable
 * @return node_t* first element that has that priority in the list
 */
node_t *return_to_bigger_priority(list_t *l, node_t *c, int priority){
    while(c != l->head && c->prev->process->priority <= priority)
        c = c->prev;
    
    return c;
}