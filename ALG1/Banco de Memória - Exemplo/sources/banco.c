#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "banco.h"

typedef struct no{
    elem info;
    int prox;
} no_t;

struct banco{
    no_t v[TAM];
    int inicio, fim, pvazio;
};

int obter_no(banco_t *b){
    assert(b != NULL);
    if(b->pvazio == -1){
        return -1;
    }
    else{
        int pos = b->pvazio;
        b->pvazio = b->v[pos].prox;
        b->v[pos].prox = -1;

        return pos;
    }
}

void liberar_no(banco_t *b, int pos){
    assert(b != NULL);
    assert(pos >= 0 && pos < TAM);
    b->v[pos].prox = b->pvazio;
    b->pvazio = pos;
}

banco_t *criar(){
    banco_t *b = (banco_t *)malloc(sizeof(banco_t));

    for(int i = 0; i < TAM - 1; i++){
        b->v[i].prox = i + 1;
    }

    b->v[TAM-1].prox = -1;
    b->pvazio = 0;
    b->inicio = -1;
    b->fim = -1;

    return b;
}

int esta_vazio(banco_t *b){
    assert(b != NULL);
    return b->inicio == -1;
}

int esta_cheio(banco_t *b){
    assert(b != NULL);
    return b->pvazio == -1;
}

int inserir(banco_t *b, elem x){
    int pos = obter_no(b);
    if(pos == -1){
        return 0;
    }

    b->v[pos].info = x;
    b->v[b->fim].prox = pos;
    b->fim = pos;
    if(b->inicio == -1)
        b->inicio = pos;
    
    return 1;
}

int remover(banco_t *b, elem *x){
    assert(b != NULL);
    if(b->inicio == -1)
        return 0;
    
    *x = b->v[b->inicio].info;
    int pos = b->inicio;
    b->inicio = b->v[pos].prox;
    liberar_no(b, pos);

    return 1;
}

void liberar(banco_t *b){
    free(b);
}