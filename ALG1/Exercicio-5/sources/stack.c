#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct stack{
    int top;
    char data[stackSize];
};

/**
 * @brief creates a stack
 * 
 * @return stack_t* stack pointer
 */
stack_t *create(){
    stack_t *s = (stack_t *)malloc(sizeof(stack_t));
    s->top = -1;
    return s;
}

/**
 * @brief deletes a stack
 * 
 * @param s stack struct
 */
void delete(stack_t *s){
    free(s);
}

/**
 * @brief checks if a stack is full
 * 
 * @param s stack struct
 * @return int 1 is true, 0 is false
 */
int isFull(stack_t *s){
    if(s->top == stackSize -1)
        return 1;
    return 0;
}

/**
 * @brief checks if a stack is empty
 * 
 * @param s stack struct
 * @return int int 1 is true, 0 is false
 */
int isEmpty(stack_t *s){
    if(s->top == -1)
        return 1;
    return 0;
}

/**
 * @brief pushes a item to the stack
 * 
 * @param s stack struct
 * @param x variable to be stacked
 * @return int returns whether a push was successfull or not
 */
int push(stack_t *s, char x){
    if(isFull(s) == 1)
        return -1;

    s->top++;
    s->data[s->top] = x;
    return 1;
}

/**
 * @brief pops a item off stack
 * 
 * @param s stack struct
 * @param x variable that will store the popped value
 * @return int returns whether a pop was successfull or not
 */
int pop(stack_t *s, char *x){
    if(isEmpty(s) == 1)
        return -1;
    
    *x = s->data[s->top];
    s->top--;
    return 1;
}

/**
 * @brief view the top value of the stack
 * 
 * @param s stack struct
 * @param x variable that will hold the value
 * @return int returns whether a top was successfull or not
 */
int top(stack_t *s, char *x){
    if(isEmpty(s) == 1)
        return -1;
    
    *x = s->data[s->top];
    return 1;
}