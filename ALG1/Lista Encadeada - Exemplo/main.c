#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;

struct node{
    int info;
    node_t *next;
};


int main(int argc, char *argv[]){
    node_t *start, *end, *p;
    start = NULL;
    end = NULL;

    int input;
    scanf(" %d", &input);
    while(input != -1){
        p = (node_t *)malloc(sizeof(node_t));
        p->info = input;
        p->next = NULL;

        if(start == NULL){
            start = p;
            end = p;
        }
        else{
            end->next = p;
            end = p;
        }
        scanf(" %d", &input);
    }

    p = start;
    while(p != NULL){
        printf("%d ", p->info);
        p = p->next;
    }
    printf("\n");

    while(start != NULL){
        p = start;
        start = start->next;
        free(p);
    }

    return 0;
}