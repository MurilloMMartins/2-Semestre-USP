#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "listagen.h"

void libera(no_t *p){
    no_t *aux;

    while(p != NULL){
        if(p->tipo == 1){
            libera(p->info.subLista);
        }
        aux = p;
        p = p->prox;
        free(aux);
    }
}

no_t *atomo(elem x){
    no_t *p = (no_t *)malloc(sizeof(no_t));
    p->tipo = 0;
    p->prox = NULL;
    p->info.atomo = x;
    return p;
}

no_t *sublista(no_t *sublista){
    no_t *p = (no_t*)malloc(sizeof(no_t));
    p->tipo = 1;
    p->prox = NULL;
    p->info.subLista = sublista;
    return p;
}

no_t *concat(no_t *p, no_t *q){
    assert(p != NULL);
    p->prox = q;
    return p;
}

info_t cabeca(no_t *p, int *tipo){
    assert(p != NULL);
    *tipo = p->tipo;
    return p->info;
}

no_t *cauda(no_t *p){
    assert(p != NULL);
    return p->prox;
}

void imprime(no_t *p){
    if(p == NULL)
        return;
    printf("(");
    while(p != NULL){
        if(p->tipo == 0)
            printf("%d", p->info.atomo);
        else
            imprime(p->info.subLista);

        if(p->prox != NULL)
            printf(", ");
        p = p->prox;
    }
    printf(")");
}

void imprimir(no_t *p){
    imprime(p);
    printf("\n");
}

