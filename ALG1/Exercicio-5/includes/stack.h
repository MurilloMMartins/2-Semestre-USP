#ifndef NAME_H
#define NAME_H

#define stackSize 400

typedef struct stack stack_t;

stack_t *create();
void delete(stack_t *s);
int isFull(stack_t *s);
int isEmpty(stack_t *s);
int push(stack_t *s, char x);
int pop(stack_t *s, char *x);
int top(stack_t *s, char *x);

#endif