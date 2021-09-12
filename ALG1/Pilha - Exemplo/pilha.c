#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "pilha.h"

struct pilha {
    int topo;
    void **itens;
    int tamElem;
};

pilha_t *create(int tamElem){
    pilha_t *p = (pilha_t *)malloc(sizeof(pilha_t));
    assert(p != NULL);

    p->itens = (void **)malloc(sizeof(void *) * TamPilha);
    assert(p->itens != NULL);

    p->topo = -1;
    p->tamElem = tamElem;

    return p;
}

void destroy(pilha_t *p){
    while(p->topo >= 0){
        free(p->itens[p->topo]);
        p->topo -= 1;
    }

    if(p->itens != NULL)
        free(p->itens);

    if(p != NULL)
        free(p);

    p = NULL;
}

int isFull(pilha_t *p){
    assert(p != NULL);

    if(p->topo == TamPilha - 1)
        return 1;
    else
        return 0;
}

int isEmpty(pilha_t *p){
    assert(p != NULL);

    if(p->topo == -1)
        return 1;
    else
        return 0;
}

int push(pilha_t *p, void *x){
    assert(p != NULL);

    if(isFull(p) == 1){
        return -1;
    }

    p->topo = p->topo + 1;
    p->itens[p->topo] = (void *)malloc(p->tamElem);
    assert(p->itens[p->topo] != NULL);

    memcpy(p->itens[p->topo], x, p->tamElem);
    return 1;
}

int pop(pilha_t *p, void *x){
    assert(p != NULL);

    if(isEmpty(p) == 1){
        return -1;
    }

    memcpy(x, p->itens[p->topo], p->tamElem);
    free(p->itens[p->topo]);
    p->topo -= 1;
    return 1;
}

int top(pilha_t *p, void *x){
    assert(p != NULL);

    if(isEmpty(p) == 1){
        return -1;
    }

    memcpy(x, p->itens[p->topo], p->tamElem);
    return 1;
}